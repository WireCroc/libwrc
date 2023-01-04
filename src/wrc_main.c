#include "./wrc/wrc.h"

// void custom_func(wc_pa pa) {
//     fprintf(fp, "\n%s\n%s", pa.eth.source, pa.eth.dest);
// } 

int main(void) {
    wrc cap;
    wc_iflist ifc = wrc_get_interfaces();
    
    wrc_default(&cap);

    int opts = wrc_setopts(&cap, ifc.ifc[2], PA_NULL, 0);
    if (opts != 0) {
        printf("setopts error\n");
        exit(0);
    }
    //               custom_func
    wrc_cap(&cap, 1, DEFAULT_CAP);  
    wrc_destroy(&cap);
        
    return 0; 
}
