#ifndef MASTER_H
#define MASTER_H

#include <soem/soem.h>
#include <soem/osal.h>
#include <stdint.h>
#include <time.h>
#include "modes.h"

typedef struct {
    uint8_t io_map[4096];
    output_csp_t *outputs;
    input_csp_t *inputs;
    int reference_clock;
    struct timespec clock;
} ec_master;

int setup(const char *ifname);
void run();
void ec_sync(int64_t reftime, int64_t cycletime , int64_t *offsettime);
OSAL_THREAD_FUNC_RT ecatthread(void *ptr);

#endif // MASTER_H
