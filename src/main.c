#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <soem/ethercat.h>
#include <soem/osal.h>

#include "interface.h"
#include "master.h"

static pthread_t thread1;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <ifname>\n", argv[0]);
        print_all_interfaces(stderr);
        exit(EXIT_FAILURE);
    }

    if (!is_valid_interface(argv[1]))
    {
        fprintf(stderr, "Invalid interface!\n");
        print_all_interfaces(stderr);
        exit(EXIT_FAILURE);
    }

    mlockall(MCL_CURRENT);
    if (!setup(argv[1]))
        exit(EXIT_FAILURE);
    run();
    munlockall();
    exit(EXIT_SUCCESS);
}
