#ifndef MASTER_H
#define MASTER_H

#include <soem/ethercat.h>
#include <stdint.h>
#include "mode.h"

typedef struct {
    uint8_t io_map[4096];
    output_csv_t *outputs;
    input_csv_t *inputs;
} ec_master;

int setup(const char *ifname);
void run();

#endif // MASTER_H
