#ifndef WRC_H
#define WRC_H

#pragma once

#include "../utils/utils.h"
#include "../eth/eth.h"
#include "../ip/ip.h"
#include "../arp/arp.h"
#include "../tcp/tcp.h"
#include "../udp/udp.h"

typedef enum {
    PA_NULL = 0,
    PA_IP,
    PA_ARP,
    PA_TCP,
    PA_UDP,
    PA_ETH
} pa;

typedef struct {
    wc_eth eth;
    union {
        wc_arp arp;
        wc_ip ip;
        wc_tcp tcp;
        wc_udp udp;
    };
    pa p[MAX_PA];
} wc_pa;

typedef struct {
    char name[MAX_IFNAME];
    uint64_t mtu;
    uint8_t flag;
} wc_iface;

typedef struct {
    wc_iface ifc[MAX_IFACE];
    uint8_t len;
} wc_iflist;

typedef struct {
    int fd;
    int32_t recvl;
    uint64_t recvn;
    wc_iface iface;
    pa ign_pa;
    int8_t flag;
    struct sockaddr saddr;
    union {
        unsigned char *recv;
    };
} wrc;

void wrc_default(wrc*); 
void wrc_destroy(wrc*);

int8_t wrc_setopts(wrc*, wc_iface, pa, int8_t);
int8_t wrc_run_loop(wrc*, void (*cb)(wrc* a));
int8_t wrc_run_(wrc*);
wc_iflist wrc_get_interfaces(void);

// private fucs
wc_pa wrc_get_packets(wrc*);
void wc_pa_set(wc_pa*);

#endif
