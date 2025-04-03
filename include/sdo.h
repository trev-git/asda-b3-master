#ifndef SDO_H
#define SDO_H

#include <stdint.h>
#include <stdbool.h>

uint8_t sdo_read8(int slave, uint16_t index, uint8_t subindex);
uint16_t sdo_read16(int slave, uint16_t index, uint8_t subindex);
uint32_t sdo_read32(int slave, uint16_t index, uint8_t subindex);
bool sdo_write8(int slave, uint16_t index, uint8_t subindex, uint8_t val);
bool sdo_write16(int slave, uint16_t index, uint8_t subindex, uint16_t val);
bool sdo_write32(int slave, uint16_t index, uint8_t subindex, uint32_t val);

#endif // SDO_H
