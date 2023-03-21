#ifndef WC_UDP_H
#define WC_UDP_H

#pragma once

#include "../utils/utils.h"
#include "../ip/ip.h"
#include <netinet/udp.h>

typedef struct udphdr wc_udphdr;

typedef struct {
    uint16_t source;
    uint16_t dest;
    uint16_t len;
    uint16_t check;
    void* pl;
} wc_udp;

void wc_udp_p(const unsigned char*, wc_udp*, uint16_t, wc_ip*);

#endif
