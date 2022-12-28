#ifndef WRC_H
#define WRC_H

#pragma once

#include "utils.h"
#include "eth.h"
#include "ip.h"
#include "arp.h"
#include "tcp.h"
#include "udp.h"

typedef enum {
    PA_ETH = 0,
    PA_IP,
    PA_ARP,
    PA_TCP,
    PA_UDP,
    PA_NULL
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
    wc_iface* ifc;
    uint8_t len;
} wc_iflist;

typedef struct {
  SOCKET fd;
  int32_t recvl;
  uint64_t recvn;
  wc_iface *iface;
  struct sockaddr *saddr;
  union {
    wc_pa pa;
    unsigned char *recv;
  };
} wrc;

void wrc_default(wrc*); 
void wrc_destroy(wrc*);

int8_t wrc_setopts(wrc*, char*, pa, int8_t);
int8_t wrc_run_loop(wrc*, void (*cb)(wrc* a));
int8_t wrc_run_(wrc*);
wc_iflist wrc_get_interfaces(void);

// private fucs
void wrc_get_packets(wrc*);

#endif
