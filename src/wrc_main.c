#include <stdio.h>
#include <stdlib.h>
#include "wrc.h"

int main(void) {
//    wrc cap;
    wc_iflist ifc;
    
//    wrc_default(&cap);

    ifc = wrc_get_interfaces();

    printf("Interface: %s\nInterface: %s\nInterface: %s\nLen %d\n", ifc.ifc[0].name, ifc.ifc[1].name, ifc.ifc[2].name, ifc.len);

//    wrc_destroy(&cap);
    free(ifc.ifc);
    
    return 0; 
}
