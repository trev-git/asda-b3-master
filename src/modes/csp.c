#include <stdint.h>

#include <soem/soem.h>

#include "asda-b3.h"
#include "sdo.h"

int csp_pdo(ecx_contextt *ctx, uint16_t slave)
{
    /* disable PDO configuration */
    sdo_write8(ctx, slave, SM2, 0, 0);
    sdo_write8(ctx, slave, SM3, 0, 0);

    /* disable PDO mapping */
    sdo_write8(ctx, slave, RXPDO, 0, 0);
    sdo_write8(ctx, slave, TXPDO, 0, 0);

    /* map RxPDO for Cyclic Synchronous Position mode */
    sdo_write32(ctx, slave, RXPDO, 1, ((PROFILE_MODE << 16) + 0x08));
    sdo_write32(ctx, slave, RXPDO, 2, ((TARGET_POSITION << 16) + 0x20));
    sdo_write32(ctx, slave, RXPDO, 3, ((CONTROL_WORD << 16) + 0x10));
    sdo_write8(ctx, slave, RXPDO, 0, 3);

    /* map TxPDO for Cyclic Synchronous Position mode mode */
    sdo_write32(ctx, slave, TXPDO, 1, ((STATUS_WORD << 16) + 0x10));
    sdo_write32(ctx, slave, TXPDO, 2, ((POSITION_ACTUAL << 16) + 0x20));
    sdo_write8(ctx, slave, TXPDO, 0, 2);

    /* set PDO mapping */
    sdo_write16(ctx, slave, SM2, 1, RXPDO);
    sdo_write16(ctx, slave, SM3, 1, TXPDO);

    /* enable PDO configuration */
    sdo_write8(ctx, slave, SM2, 0, 1);
    sdo_write8(ctx, slave, SM3, 0, 1);

    return 1;
}