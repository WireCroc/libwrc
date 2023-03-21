#include "udp.h"

void wc_udp_p(const unsigned char *in, wc_udp *out, uint16_t ihl, wc_ip* prev) {
    struct udphdr *udp = (struct udphdr *)(in + (ihl * 4) + sizeof(struct ethhdr));
    out->source = ntohs(udp->source);
    out->dest = ntohs(udp->dest);
    out->check = ntohs(udp->check);
    out->len = ntohs(udp->len);

    out->pl = NULL;
    prev->pl = (void*)out;
}
// parse udp header
