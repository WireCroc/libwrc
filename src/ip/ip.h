#ifndef WC_IP_H
#define WC_IP_H

#pragma once

#include "../utils/utils.h"
#include "../eth/eth.h"

#include <net/ethernet.h>
#include <netinet/ip.h>

typedef struct iphdr wc_iphdr;

typedef struct {
    uint8_t version;
    int32_t ttl;
    int32_t ihl;
    int16_t tos;
    int64_t tl;
    int16_t ident;
    int32_t hchs;
    unsigned char* source;
    unsigned char* dest;
    uint8_t proto;
} wc_ip; // ip struct definition

void wc_ip_p(const unsigned char* in, wc_ip* out);

#endif
