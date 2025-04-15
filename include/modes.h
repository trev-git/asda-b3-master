#ifndef MODE_H
#define MODE_H

#include <stdint.h>

#define MODE_PROFILE_POSITION 0x01
#define MODE_CYCLIC_SYNCHRONOUS_POSITION 0x08
#define MODE_PROFILE_VELOCITY 0x03

typedef int (*Mode)(uint16_t);

typedef struct __attribute__((packed)) {
    uint8_t mode;
    uint16_t control_word;
    int32_t target_position;
    uint32_t profile_velocity;
    uint32_t profile_acceleration;
    uint32_t profile_deceleration;
} output_pp_t;

typedef struct __attribute__((packed)) {
    uint16_t status_word;
    int32_t actual_target;
} input_pp_t;

typedef struct __attribute__((packed)) {
    uint8_t mode;
    int32_t target_position;
    uint16_t control_word;
} output_csp_t;

typedef struct __attribute__((packed)) {
    uint16_t status_word;
    int32_t actual_target;
} input_csp_t;

int pp_pdo(uint16_t slave);
int pv_pdo(uint16_t slave);
int csp_pdo(uint16_t slave);
int csv_pdo(uint16_t slave);

#endif // MODE_H
