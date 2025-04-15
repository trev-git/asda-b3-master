#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <stdbool.h>

uint8_t read_ec_reg8(uint16_t slave_addr, uint16_t reg);
bool write_ec_reg8(uint16_t slave_addr, uint16_t reg, uint8_t data);

#endif // REGISTERS_H
