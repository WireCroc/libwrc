#ifndef WC_UTILS_H
#define WC_UTILS_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <time.h>

#define OK 0
#define ERR 1

#define MAX_TEXTFORMAT_BUFFERS 2048
#define MAX_TEXT_BUFFER_LENGTH 2048

#define MAX_PA 3
#define MAX_IFACE 10
#define MAX_IFNAME 16

#define TCP 6
#define UDP 17

typedef int SOCKET;

void todo(FILE *, const char *, int);
char *wc_format(const char *, ...);

#endif
