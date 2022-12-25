#ifndef WC_ETH_H
#define WC_ETH_H

#pragma once

#include "utils.h"

#include <net/ethernet.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define IP htons(ETHERTYPE_IP)
#define ARP htons(ETHERTYPE_ARP)
#define DEFAULT (int8_t) 254

typedef struct ethhdr wc_ethdr;

typedef struct {
    unsigned char* source;
    unsigned char* dest;
    char* proto;
} wc_eth;

void wc_eth_parse(const unsigned char* in, wc_eth* out);

#endif
