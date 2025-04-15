#include <soem/ethercat.h>
#include <stdint.h>
#include "state.h"

uint16_t set_ec_state(uint16_t slave, ec_state state)
{
    ec_slave[slave].state = state;
    ec_writestate(slave);
    do {
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
    } while (ec_statecheck(slave, state, EC_TIMEOUTSTATE) != state);
    return ec_slave[slave].state;
}
