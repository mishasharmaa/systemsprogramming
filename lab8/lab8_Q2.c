#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netdb.h>


// Question 2: Filtering IPv4 and IPv6 Interfaces
int main() {
    struct ifaddrs *addresses;
    if (getifaddrs(&addresses) == -1) {
        printf("Error getting network info\n");
        return 1;
    }
    
    struct ifaddrs *address = addresses;
    while (address) {
        char name[100];
        int size;
        int family = address->ifa_addr->sa_family;
            if (family == AF_INET || family == AF_INET6) {
                if(family == AF_INET){
                    size = sizeof(struct sockaddr_in);
                } else {
                    size = sizeof(struct sockaddr_in6);
                }
                getnameinfo(address->ifa_addr, size, name, sizeof(name), 0, 0, 0);
                printf("Interface Name for %s: %s\n", 
                       (family == AF_INET) ? "IPv4" :"IPv6", 
                       name);
            }    
        address = address->ifa_next;
    }
    freeifaddrs(addresses);
    return 0;
}
