#ifndef ASDAB3_H
#define ASDAB3_H

/* PDO addresses */
#define RXPDO 0x1601
#define TXPDO 0x1a01
#define SM2   0x1c12
#define SM3   0x1c13

/* RxPDO addresses */
#define PROFILE_MODE     0x6060
#define CONTROL_WORD     0x6040
#define TARGET_POSITION  0x607a
#define TARGET_VELOCITY  0x60ff
#define PROFILE_VELOCITY 0x6081
#define PROFILE_ACCEL    0x6083
#define PROFILE_DECEL    0x6084

/* TxPDO addresses*/
#define STATUS_WORD      0x6041
#define POSITION_ACTUAL  0x6064

#endif // ASDAB3_H