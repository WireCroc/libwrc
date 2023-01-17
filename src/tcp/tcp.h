#ifndef WC_TCP_H
#define WC_TCP_H

#pragma once

#include "../utils/utils.h"
#include "../eth/eth.h"
#include <netinet/tcp.h>

typedef struct tcphdr wc_tcphdr;

typedef struct {
    uint16_t source;
    uint16_t dest;
    uint32_t sequence;
    uint32_t ack_sequence;
    uint16_t window;
    uint16_t checksum;
    uint8_t flag;
} wc_tcp; // tcp struct definition

void wc_tcp_p(const unsigned char*, wc_tcp*, uint16_t);

#endif
