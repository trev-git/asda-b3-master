#ifndef SDO_H
#define SDO_H

#include <soem/soem.h>
#include <stdint.h>
#include <stdbool.h>

bool sdo_read8(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint8_t *val);
bool sdo_read16(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint16_t *val);
bool sdo_read32(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint32_t *val);
bool sdo_write8(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint8_t val);
bool sdo_write16(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint16_t val);
bool sdo_write32(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint32_t val);

#endif // SDO_H
