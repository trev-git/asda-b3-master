#include <soem/ethercattype.h>
#include <stdio.h>
#include <signal.h>
#include <soem/ethercat.h>
#include <soem/osal.h>
#include <stdint.h>
#include <time.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

#include "master.h"
#include "dc.h"
#include "modes.h"
#include "pdo.h"
#include "sdo.h"
#include "state.h"

static ec_master master = { 0 };
volatile static int do_run = 1;
static int64_t gl_delta, toff, dorun;
static int8_t *digout = 0;
static pthread_t ec_thread;
static const int cycletime = 4000000; // in ns
static int cycles = 0;
volatile static int target_position;

void signal_handler(int sig)
{
    if (sig == SIGTERM || sig == SIGINT)
    {
        do_run = 0;
    }
}

/**
 * @fn int setup(const char *ifname)
 * @brief Setup the slaves.
 *
 * Initialize the NIC interface, perform preliminary setup
 * before going to Operational mode.
 * @param ifname Interface name to initialize.
 * @return 1 on success, 0 on fail.
 */

int setup(const char *ifname)
{
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

#pragma region Init state
    if (!ec_init(ifname))
    {
        fprintf(stderr, "Failed to initialize EtherCAT on %s! Maybe try with sudo?\n", ifname);
        return 0;
    }
#pragma endregion

#pragma region Pre-Operational state
    if (ec_config_init(FALSE) < 0)
    {
        fprintf(stderr, "No slaves found!\n");
        return 0;
    }
    printf("Found %d slaves.\n", ec_slavecount);
    uint16_t state = set_ec_state(0, EC_STATE_PRE_OP);

    ec_slave[1].PO2SOconfig = csp_pdo;
    ec_configdc();
    ec_dcsync0(1, TRUE, cycletime, 0);
    // master.reference_clock = get_reference_clock();
    // bzero(master.io_map, 4096);
    ec_config_map(master.io_map);
    master.outputs = (output_csp_t *)ec_slave[1].outputs;
    master.inputs = (input_csp_t *)ec_slave[1].inputs;
    printf("Set state to PRE_OP\n");
    // SDO 0x1c32 0x01 - отличное от нуля
#pragma endregion

#pragma region Safe Operational state
    set_ec_state(0, EC_STATE_SAFE_OP);
    printf("Set state to SAFE_OP\n");
#pragma endregion

#pragma region Operational state
    set_ec_state(0, EC_STATE_OPERATIONAL);

    master.outputs->mode = MODE_CYCLIC_SYNCHRONOUS_POSITION;
    write_pdo(cycletime / 1000);
    master.outputs->target_position = master.inputs->actual_target;
    target_position = master.outputs->target_position;
    write_pdo(cycletime / 1000);
    sdo_write32(1, 0x607f, 0, 40000);

    osal_thread_create_rt(&ec_thread, 64 * 1024, ecatthread, (void *)&cycletime);
    printf("Configured all slaves and set Operational state\n");
#pragma endregion

    return 1;
}

void run()
{
    master.outputs->control_word = 0b00110;
    write_pdo(cycletime / 1000);
    master.outputs->control_word = 0b00111;
    write_pdo(cycletime / 1000);
    master.outputs->control_word = 0b01111;
    write_pdo(cycletime / 1000);

    dorun = 1;
    for(int i = 1; i <= 1000; i++)
    {
        printf("i: %ld ", dorun);
        printf(" O:");
        printf("cur_vel=%d ", sdo_read32(1, 0x606c, 0));
        printf("target_pos=%d ", sdo_read32(1, 0x607a, 0x00));
        for(int j = 0 ; j < ec_slave[1].Obytes; j++)
        {
            printf(" %2.2x", ec_slave[1].outputs[j]);
        }
        printf(" I:");
        for(int j = 0 ; j < ec_slave[1].Ibytes; j++)
        {
            printf(" %016b", ec_slave[1].inputs[j]);
        }
        printf("\r");
        fflush(stdout);
        osal_usleep(20000);
    }

    set_ec_state(0, EC_STATE_INIT);
    printf("\nDone\n");
    ec_close();
}

void ec_sync(int64 reftime, int64 cycletime , int64 *offsettime)
{
   static int64 integral = 0;
   int64 delta;
   /* set linux sync point 50us later than DC sync, just as example */
   delta = (reftime - 50000) % cycletime;
   if(delta> (cycletime / 2)) { delta= delta - cycletime; }
   if(delta>0){ integral++; }
   if(delta<0){ integral--; }
   *offsettime = -(delta / 100) - (integral / 20);
   gl_delta = delta;
}

OSAL_THREAD_FUNC_RT ecatthread(void *ptr)
{
    struct timespec ts, tleft;
    int ht;
    int64_t cycletime;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    ht = (ts.tv_nsec / 1000000) + 1; /* round to nearest ms */
    ts.tv_nsec = ht * 1000000;
    if (ts.tv_nsec >= NS_PER_SEC)
    {
        ts.tv_sec++;
        ts.tv_nsec -= NS_PER_SEC;
    }
    cycletime = *(int*)ptr; /* cycletime in ns */
    toff = 0;
    dorun = 0;
    // ec_send_processdata();
    while(1)
    {
        /* calculate next cycle start */
        add_timespec(&ts, cycletime + toff);
        /* wait to cycle start */
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, &tleft);
        if (dorun>0)
        {
            ((output_csp_t *)ec_slave[1].outputs)->target_position = target_position;
            target_position += 10000;

            // printf("pos=%d\n", master.outputs->target_position);
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);

            dorun++;
            /* if we have some digital output, cycle */
            // if( digout ) *digout = (uint8) ((dorun / 16) & 0xff);

            if (ec_slave[0].hasdc)
            {
                /* calculate toff to get linux time and DC synced */
                ec_sync(ec_DCtime, cycletime, &toff);
            }
        }
    }
}
