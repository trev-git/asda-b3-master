#include <stdio.h>
#include <stdint.h>
#include <soem/ethercat.h>
#include <soem/osal.h>

#include "pdo.h"

int write_pdo(int timeout)
{
    if (ec_send_processdata() <= 0)
    {
        fprintf(stderr, "[WARN] Couldn't transmit PDO!\n");
        return -1;
    }
    int wkc = ec_receive_processdata(EC_TIMEOUTRET);
    if (timeout)
        osal_usleep(timeout);
    return wkc;
}
