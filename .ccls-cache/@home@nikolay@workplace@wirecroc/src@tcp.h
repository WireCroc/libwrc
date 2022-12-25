#ifndef WC_TCP_H
#define WC_TCP_H

#pragma once

#include "utils.h"
#include <netinet/tcp.h>

typedef tcphdr wc_tcp;

void wc_tcp_p(const unsigned char*, wc_tcp*, uint16_t);

#endif 
