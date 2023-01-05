#ifndef WC_ARP_H
#define WC_ARP_H

#pragma once

#include "../utils/utils.h"
#include "../eth/eth.h"

#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if_arp.h>

typedef struct {
    unsigned short int ar_hrd;                /* Format of hardware address.  */
    unsigned short int ar_pro;                /* Format of protocol address.  */
    unsigned char ar_hln;                /* Length of hardware address.  */
    unsigned char ar_pln;                /* Length of protocol address.  */
    unsigned short int ar_op;                /* ARP opcode (command).  */
    unsigned char __ar_sha[ETH_ALEN];        /* Sender hardware address.  */
    unsigned char __ar_sip[4];                /* Sender IP address.  */
    unsigned char __ar_tha[ETH_ALEN];        /* Target hardware address.  */
    unsigned char __ar_tip[4];                /* Target IP address.  */
} wc_arphdr; // arp header definition

typedef struct {
    char *hw_t;
    char *p_t;
    uint8_t hw_len;
    uint8_t p_len;
    char *opcode;
    char *sender_mac;
    char *sender_ip;
    char *target_mac;
    char *target_ip;
} wc_arp; // arp struct definition

void wc_arp_p(const unsigned char* in, wc_arp* out);

#endif
