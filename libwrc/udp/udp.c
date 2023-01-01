#include "udp.h"

void wc_udp_p(const unsigned char *in, wc_udp *out, uint16_t ihl) {
    out = (wc_udp *)(in + (ihl * 4));
}
