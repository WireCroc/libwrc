#include "tcp.h"

void wc_tcp_p(const unsigned char *in, wc_tcp *out, uint16_t ihl) {
    wc_tcphdr* tcp = (wc_tcphdr*)(in + (ihl * 4));
    out->source = tcp->source;
    out->dest = tcp->dest;
    out->sequence = tcp->seq;
    out->ack_sequence = tcp->ack_seq;
    out->window = tcp->window;
    out->checksum = tcp->check;
    out->flag = tcp->th_flags;
}