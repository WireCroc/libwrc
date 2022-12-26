#include "tcp.h"

void wc_tcp_p(const unsigned char *in, wc_tcp *out, uint16_t ihl) {
    out = (wc_tcp*)(in + (ihl * 4));
}
