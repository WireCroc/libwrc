#ifndef WRC_H
#define WRC_H

#pragma once

#include "../utils/utils.h"
#include "../eth/eth.h"
#include "../ip/ip.h"
#include "../arp/arp.h"
#include "../tcp/tcp.h"
#include "../udp/udp.h"

#define WCFILE 1
#define WCOUT 0

#define ERR_NULL 0
#define ERR_IFC 1
#define ERR_SUDO 2
#define ERR_SETOPTS 3
#define ERR_SOCK 4
#define ERR_SETSOCK 5

#define ERR_PASS (wc_err) {.code = ERR_NULL}

typedef enum {
    PA_NULL = 0,
    PA_IP,
    PA_ARP,
    PA_TCP,
    PA_UDP,
    PA_ETH
} pa; 

typedef struct {
    uint8_t code;
    char* msg;
} wc_err;

typedef struct {
    wc_eth pack;
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
    unsigned char *recv;
} wrc; 

void wrc_default(wrc *);
wc_err wrc_error(wc_err);
void wrc_destroy(wrc *);

int8_t wrc_setopts(wrc *, wc_iface, pa, int8_t);
int8_t wrc_cap(wrc *, uint8_t, wc_pa* cp, void (*cb)(wc_pa, FILE *));
void DEFAULT_CAP(wc_pa, FILE *);
wc_iflist wrc_get_interfaces(void);

// private fucs
wc_pa wrc_get_packets(wrc *);
void wc_pa_set(wc_pa *);

#endif
