#include <stdint.h>

#include "asda-b3.h"
#include "sdo.h"

int csv_pdo(uint16_t slave)
{
    /* disable PDO configuration */
    sdo_write8(slave, SM2, 0, 0);
    sdo_write8(slave, SM3, 0, 0);

    /* disable PDO mapping */
    sdo_write8(slave, RXPDO, 0, 0);
    sdo_write8(slave, TXPDO, 0, 0);

    /* map RxPDO for Cyclic Synchronous Velocity mode */
    sdo_write32(slave, RXPDO, 1, ((CONTROL_WORD << 16) + 0x10));
    sdo_write32(slave, RXPDO, 2, ((TARGET_VELOCITY << 16) + 0x20));
    sdo_write8(slave, RXPDO, 0, 2);

    /* map TxPDO for Cyclic Synchronous Velocity mode */
    sdo_write32(slave, TXPDO, 1, ((STATUS_WORD << 16) + 0x10));
    sdo_write32(slave, TXPDO, 2, ((POSITION_ACTUAL << 16) + 0x20));
    sdo_write8(slave, TXPDO, 0, 2);

    /* set PDO mapping */
    sdo_write16(slave, SM2, 1, RXPDO);
    sdo_write16(slave, SM3, 1, TXPDO);

    /* enable PDO configuration */
    sdo_write8(slave, SM2, 0, 1);
    sdo_write8(slave, SM3, 0, 1);

    return 1;
}