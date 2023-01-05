#include "eth.h"

void wc_eth_p(const unsigned char *in, wc_eth *out)
{
    wc_ethdr *hdr = (wc_ethdr *)(in);
    out->source = (unsigned char *)wc_format("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", hdr->h_source[0], hdr->h_source[1], hdr->h_source[2], hdr->h_source[3], hdr->h_source[4], hdr->h_source[5]);
    out->dest = (unsigned char *)wc_format("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", hdr->h_dest[0], hdr->h_dest[1], hdr->h_dest[2], hdr->h_dest[3], hdr->h_dest[4], hdr->h_dest[5]);
    out->proto = hdr->h_proto;
} // parse eth header
