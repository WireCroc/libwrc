CC = gcc
LFLAGS = -c -Wall -Werror -fpic

TEST = test/test.c

LOUT = bin/libwrc.so

ETH = src/eth/eth.c
ARP = src/arp/arp.c
IP = src/ip/ip.c
TCP = src/tcp/tcp.c
UDP = src/udp/udp.c
UTILS = src/utils/utils.c
WRC = src/wrc/wrc.c

.PHONY: lib

all: lib

lib: src/wrc/wrc.c
		@${CC} ${LFLAGS} ${WRC} ${ETH} ${ARP} ${IP} ${TCP} ${UDP} ${UTILS};
		@${CC} -shared -o ${LOUT} wrc.o eth.o arp.o ip.o tcp.o udp.o utils.o;
		rm -rfv wrc.o eth.o arp.o ip.o tcp.o udp.o utils.o



