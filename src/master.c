#include <soem/ethercat.h>
#include <soem/osal.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "master.h"
#include "mode.h"
#include "sdo.h"
#include "state.h"

static ec_master master = { 0 };

/**
 * @brief Setup the slaves.
 *
 * Initialize the NIC interface, perform preliminary setup
 * before going to Operational mode.
 * @param ifname Interface name to initialize.
 * @return 1 on success, 0 on fail.
 */

int setup(const char *ifname)
{
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

    ec_slave[1].PO2SOconfig = csv_pdo;
    ec_configdc();
    ec_dcsync01(0, TRUE, 5000, 5000, 0);
    ec_config_map(master.io_map);
#pragma endregion

#pragma region Safe Operational state
    set_ec_state(0, EC_STATE_SAFE_OP);
#pragma endregion

#pragma region Operational state
    set_ec_state(0, EC_STATE_OPERATIONAL);
    master.outputs = (output_csv_t *)ec_slave[0].outputs;

    master.outputs->mode = MODE_CYCLIC_SYNCHRONOUS_POSITION;
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);
    osal_usleep(5000);
    master.outputs->target_position = 100000;
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);
    osal_usleep(5000);

    master.inputs = (input_csv_t *)ec_slave[0].inputs;
    printf("Configured all slaves and set Operational state\n");
#pragma endregion

    return 1;
}

void run()
{
    master.outputs->control_word = 0b00110;
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);
    osal_usleep(5000);
    master.outputs->control_word = 0b00111;
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);
    osal_usleep(5000);
    master.outputs->control_word = 0b01111;
    ec_send_processdata();
    ec_receive_processdata(EC_TIMEOUTRET);
    osal_usleep(5000);

    for (int ticks = 0; ticks < 1000; ticks++)
    {
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
        printf("O: ");
        for (int o = 0; o < ec_slave[0].Obytes; o++)
        {
            printf("%2.2x ", ec_slave[0].outputs[o]);
        }
        printf("I: ");
        for (int i = 0; i < ec_slave[0].Ibytes; i++)
        {
            printf("%2.2x ", ec_slave[0].inputs[i]);
        }
        printf("\r");
        osal_usleep(5000);
    }
    ec_slave[0].state = EC_STATE_INIT;
    ec_writestate(0);
    printf("\nDone\n");
    ec_close();
}
