#include <interface.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ifaddrs.h>

void print_all_interfaces(FILE *stream)
{
    struct ifaddrs *ifap;

    if (getifaddrs(&ifap) < 0)
    {
        perror("getifaddrs:");
        goto print_all_interfaces_defer;
    }
    fprintf(stream, "Available network interfaces:\n");
    struct ifaddrs *tmp = ifap;
    while (tmp)
    {
        if(tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET)
            fprintf(stream, " - %s\n", tmp->ifa_name);

        tmp = tmp->ifa_next;
    }

print_all_interfaces_defer:
    if (ifap)
       freeifaddrs(ifap);
    return;
}

int is_valid_interface(char *ifname)
{
    int valid = 0;
    struct ifaddrs *ifap, *tmp;

    if (getifaddrs(&ifap) < 0)
    {
        perror("getifaddrs:");
        goto check_valid_interface_defer;
    }
    tmp = ifap;

    while (tmp)
    {
        if (!(tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET))
        {
            tmp = tmp->ifa_next;
            continue;
        }
        if (strcmp(ifname, tmp->ifa_name) == 0)
        {
            valid = 1;
            goto check_valid_interface_defer;
        }
        tmp = tmp->ifa_next;
    }

check_valid_interface_defer:
    if (ifap)
        freeifaddrs(ifap);
    return valid;
}
