# WireCroc
- WireCroc is a network traffic sniffer for Linux, macOS and other Unix 

## Example
- libwrc
```c
#include <wrc.h>

int main(void) {
    wrc cap;
    wc_iflist ifc = wrc_get_interfaces();
    
    wrc_default(&cap);

    int opts = wrc_setopts(&cap, ifc.ifc[2], PA_NULL, 0);
    if (opts != 0) {
        printf("setopts error\n");
        exit(0);
    }

    wrc_cap(&cap, 1, DEFAULT_CAP);
    
    wrc_destroy(&cap);
        
    return 0; 
}
```
