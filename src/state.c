#include "state.h"

#include <stdint.h>

#include <soem/soem.h>

uint16_t set_ec_state(ecx_contextt *ctx, uint16_t slave, ec_state state)
{
    ctx->slavelist[slave].state = state;
    ecx_writestate(ctx, slave);
    do {
        ecx_send_processdata(ctx);
        ecx_receive_processdata(ctx, EC_TIMEOUTRET);
    } while (ecx_statecheck(ctx, slave, state, EC_TIMEOUTSTATE) != state);
    return ctx->slavelist[slave].state;
}
