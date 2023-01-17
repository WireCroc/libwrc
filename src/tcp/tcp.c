#include "tcp.h"

void wc_tcp_p(const unsigned char *in, wc_tcp *out, uint16_t ihl) {
    struct tcphdr* tcp = (struct tcphdr*)(in + (ihl * 4) + sizeof(struct ethhdr));
    out->source = ntohs(tcp->source);
    out->dest = ntohs(tcp->dest);
    out->sequence = ntohs(tcp->seq);
    out->ack_sequence = ntohs(tcp->ack_seq);
    out->window = tcp->window;
    out->checksum = ntohs(tcp->check);
    out->flag = tcp->th_flags;
} 
// parse tcp header
