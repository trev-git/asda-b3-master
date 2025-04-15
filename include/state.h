#ifndef STATE_H
#define STATE_H

#include <soem/ethercat.h>
#include <stdint.h>

uint16_t set_ec_state(uint16_t slave, ec_state state);

#endif // STATE_H
