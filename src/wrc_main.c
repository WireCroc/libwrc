#include "./wrc/wrc.h"

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
    
    printf("Interfaces: %s\n%s\n%s\nLength %d\n", ifc.ifc[0].name, ifc.ifc[1].name, ifc.ifc[2].name, ifc.len);

    wrc_cap(&cap, 1, DEFAULT_CAP);
    
    wrc_destroy(&cap);
        
    return 0; 
}
