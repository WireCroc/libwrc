#include "ip.h"

void wc_ip_p(const unsigned char *in, wc_ip *out)
{
    struct sockaddr_in si, di;
    memset(&si, 0, sizeof(si));
    memset(&di, 0, sizeof(di));
    wc_iphdr *ip = (wc_iphdr *)(in + sizeof(wc_ethdr));
    si.sin_addr.s_addr = ip->saddr;
    di.sin_addr.s_addr = ip->daddr;
    out->source = (unsigned char *)inet_ntoa(si.sin_addr);
    out->dest = (unsigned char *)inet_ntoa(di.sin_addr);
    out->version = ip->version;
    out->ttl = ip->ttl;
    out->tl = ip->tot_len;
    out->ihl = ip->ihl;
    out->ident = ip->id;
    out->hchs = ip->check;
    out->tos = ip->tos;

    out->proto = ip->protocol;
} // parse ip header
