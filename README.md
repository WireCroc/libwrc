# Libwrc
**Packet capture library.**

## Installation

1. Run `make install`

## Usage

```c
#include <wrc/wrc.h>
```

## Example

```c
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

## Development

```bash
$ make lib
```

## Contributing

1. Fork it (<https://github.com/wirecroc/libwrc/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [Nikolaycc](https://github.com/nikolaycc) - creator and maintainer
- [PabloEscobar1337](https://github.com/PabloEscobar1337) - creator and maintainer
