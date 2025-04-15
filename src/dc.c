#include <soem/ethercat.h>
#include <soem/ethercatbase.h>
#include <stdio.h>
#include <time.h>

#include "dc.h"
#include "master.h"

/**
 * @fn int get_reference_clock()
 * @brief Chooses a slave to become the reference clock.
 * @returns Index of the slave chosen or -1 if no slave supports DC.
 */

int get_reference_clock()
{
    for (int i = 1; i < ec_slavecount; i++)
    {
        if (ec_slave[ec_slavecount].hasdc)
        {
            return i;
        }
    }
    return -1;
}

void set_clock(ec_master *master)
{
    clock_gettime(CLOCK_REALTIME, &master->clock);
}

void synchronize(ec_master *master)
{
    int64_t reference_time;
    clock_gettime(CLOCK_REALTIME, &master->clock);
    ec_FPRD(0x1001, 0x910, sizeof(long), &reference_time, EC_TIMEOUTRET);
    time_t master_time = master->clock.tv_sec * NS_PER_SEC + master->clock.tv_nsec;
    time_t adjusted_epoch = master_time - EC_EPOCH * NS_PER_SEC;
    printf("adjusted_epoch=%ld\n", adjusted_epoch);
    printf("reference_time=%ld\n", reference_time);
    printf("difference: %ldns\n", adjusted_epoch - reference_time);
}

struct timespec add_timespec(struct timespec *ts, int64_t add_time)
{
    int64 sec, nsec;
    nsec = add_time % NS_PER_SEC;
    sec = (add_time - nsec) / NS_PER_SEC;
    ts->tv_sec += sec;
    ts->tv_nsec += nsec;
    if ( ts->tv_nsec >= NS_PER_SEC )
    {
       nsec = ts->tv_nsec % NS_PER_SEC;
       ts->tv_sec += (ts->tv_nsec - nsec) / NS_PER_SEC;
       ts->tv_nsec = nsec;
    }
}