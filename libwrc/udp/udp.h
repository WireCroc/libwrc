#ifndef WC_UDP_H
#define WC_UDP_H

#pragma once

#include "../utils/utils.h"
#include "../ip/ip.h"
#include <netinet/udp.h>

typedef struct udphdr wc_udp;

void wc_udp_p(const unsigned char*, wc_udp*, uint16_t ihl);

#endif
