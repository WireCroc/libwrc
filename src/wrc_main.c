#include <stdio.h>
#include <stdlib.h>
#include "wrc.h"

int main(void) {
    wrc cap;
    wc_iflist ifc;
    
    wrc_default(&cap);

    ifc = wrc_get_interfaces();

    int opts = wrc_setopts(&cap, ifc.ifc[2], PA_NULL, 0);
    if (opts != 0) {
        printf("setopts error\n");
        exit(0);
    }

    printf("Interface: %s\nInterface: %s\nInterface: %s\nInterfaces Len %d\n", ifc.ifc[0].name, ifc.ifc[1].name, ifc.ifc[2].name, ifc.len);
  
    wc_pa p = wrc_get_packets(&cap);

     for (int i = 0; i < MAX_PA; i++) {
         if (p.p[i] == PA_ETH) {
             printf("PA_ETH\n");
         } else if (p.p[i] == PA_ARP) {
             printf("PA_ARP\n");
         } else if (p.p[i] == PA_IP) {
             printf("PA_IP\n");
         } else if (p.p[i] == PA_TCP) {
           printf("PA_TCP\n");
         } else if (p.p[i] == PA_UDP) {
             printf("PA_UDP\n");
         } else if (p.p[i] == PA_NULL) {
             printf("PA_NULL\n");
         }
     }

    wrc_destroy(&cap);
        
    return 0; 
}
