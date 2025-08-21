#ifndef STATE_H
#define STATE_H

#include <stdint.h>

#include <soem/soem.h>

uint16_t set_ec_state(ecx_contextt *ctx, uint16_t slave, ec_state state);

#endif // STATE_H
