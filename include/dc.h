#ifndef DC_H
#define DC_H

#include <time.h>
#include "master.h"

#define NS_PER_SEC (1000000000LL)
#define EC_EPOCH (946684800LL)
#define TIMESPEC_NS(ts) ((ts.tv_sec * NS_PER_SEC) + ts.tv_nsec)
#define TO_EC_EPOCH(nsec) ((int64_t)nsec - EC_EPOCH)

int get_reference_clock();
void synchronize(ec_master *master);
void set_clock(ec_master *master);
struct timespec add_timespec(struct timespec *ts1, int64_t add_time);

#endif // DC_H
