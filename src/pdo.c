#include "pdo.h"

#include <stdio.h>
#include <stdint.h>

#include <soem/soem.h>
#include <soem/osal.h>

int write_pdo(ecx_contextt *ctx, int timeout)
{
    if (ecx_send_processdata(ctx) <= 0)
    {
        fprintf(stderr, "[WARN] Couldn't transmit PDO!\n");
        return -1;
    }
    int wkc = ecx_receive_processdata(ctx, EC_TIMEOUTRET);
    if (timeout)
        osal_usleep(timeout);
    return wkc;
}
