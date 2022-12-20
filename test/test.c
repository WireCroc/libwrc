#include <stdio.h>
#include <stdlib.h>

#include <string.h> // memset
#include <unistd.h> // close syscall
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <netinet/ether.h>
#include <netinet/tcp.h> // TCP header
#include <netinet/udp.h> // UDP header
#include <netinet/ip_icmp.h> // ICMP header
#include <netinet/ip.h> // IP header
#include <sys/socket.h> // Socket's APIs
#include <arpa/inet.h> // inet_ntoa
#include <signal.h> // signal

#include "../src/eth.h"
#include "../src/ip.h"

int main(void) {
    unsigned char *buf = (unsigned char *) malloc(65536); //to receive data
    memset(buf, 0, 65536);
    struct sockaddr addr;
    struct sockaddr_in source, dest;
    int sock, data, size;
    wc_eth eth;
    wc_ip ip;

    printf("Stage 1: init sock");
    sock = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
    if (sock < 0)
        exit(1);

    printf("Stage 2: capture packets");
    while (1) {
        size = sizeof(addr);

        data = recvfrom(sock, buf, 65536, 0, &addr, (socklen_t *)&size);
        if (data < 0) {
            fprintf(stderr, "Cant get packets!");
            break;
        } else {
            wc_eth_parse(buf, &eth);
            wc_ip_parse(buf, &ip);
            printf("\n ************************************* \nETH: \n\tSource: %s\n\tDest: %s\n\tProtocol: %s\nIP: \n\tSource IP: %s\n\tDest Ip: %s\n\tVersion: %d\n\tTTL: %d\n\tProtocol: %s", eth.source, eth.dest, eth.proto, ip.source, ip.dest, ip.version, ip.ttl, ip.proto);
        }
    }

    printf("Stage 3: close sock");
    close(sock);
    free(buf);

    return 0;
}
