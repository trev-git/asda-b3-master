#include "sdo.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <soem/soem.h>

bool sdo_read8(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint8_t *val)
{
    int size = sizeof(val);
    if (ecx_SDOread(ctx, slave, index, subindex, FALSE, &size, val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to read at %04x:%02x!\n", index, subindex);
    }
    return val;
}

bool sdo_read16(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint16_t *val)
{
    int size = sizeof(val);
    if (ecx_SDOread(ctx, slave, index, subindex, FALSE, &size, val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to read at %04x:%02x!\n", index, subindex);
    }
    return val;
}

bool sdo_read32(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint32_t *val)
{
    int size = sizeof(val);
    if (ecx_SDOread(ctx, slave, index, subindex, FALSE, &size, val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to read at %04x:%02x!\n", index, subindex);
    }
    return val;
}

bool sdo_write8(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint8_t val)
{
    if (ecx_SDOwrite(ctx, slave, index, subindex, FALSE, sizeof(val), &val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to write %02x to %04x:%02x!\n", val, index, subindex);
        return false;
    }
    return true;
}

bool sdo_write16(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint16_t val)
{
    if (ecx_SDOwrite(ctx, slave, index, subindex, FALSE, sizeof(val), &val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to write %04x to %04x:%02x!\n", val, index, subindex);
        return false;
    }
    return true;
}

bool sdo_write32(ecx_contextt *ctx, int slave, uint16_t index, uint8_t subindex, uint32_t val)
{
    if (ecx_SDOwrite(ctx, slave, index, subindex, FALSE, sizeof(val), &val, EC_TIMEOUTSAFE) == 0)
    {
        fprintf(stderr, "Failed to write %08x to %04x:%02x!\n", val, index, subindex);
        return false;
    }
    return true;
}
