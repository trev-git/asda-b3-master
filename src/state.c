#include <soem/ethercat.h>
#include <soem/ethercatmain.h>
#include <stdint.h>
#include "state.h"

void set_ec_state(uint16_t slave, ec_state state)
{
    ec_slave[slave].state = state;
    ec_writestate(slave);
    do {
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
    } while (ec_statecheck(slave, state, EC_TIMEOUTSTATE));
}
