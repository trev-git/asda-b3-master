#include <stdio.h>
#include <stdlib.h>
#include <interface.h>
#include <master.h>
#include <soem/ethercat.h>

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

    if (!setup(argv[1]))
        exit(EXIT_FAILURE);
    run();

    exit(EXIT_SUCCESS);
}
