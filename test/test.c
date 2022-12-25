#include <stdio.h>
#include <stdlib.h>

#include <string.h> // memset
#include <unistd.h> // close syscall
#include <sys/socket.h> // Socket's APIs
#include <arpa/inet.h> // inet_ntoa
#include <signal.h> // signal
#include <netinet/tcp.h> //tcp header
#include <netinet/udp.h> //udp header

#include "../src/eth.h"
#include "../src/ip.h"
#include "../src/arp.h"

int main(void) {
    unsigned char *buf = (unsigned char *) malloc(65536); //to receive data
    memset(buf, 0, 65536);
    struct sockaddr addr;
    struct sockaddr_in source, dest;
    int sock, data, size;
    wc_eth eth;
    wc_ip ip;
    wc_arp arp;

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
            wc_eth_p(buf, &eth);
            if (strcmp(eth.proto, "IP") == 0) {
                wc_ip_p(buf, &ip);
               printf("\n ************************************* \nETH: \n\tSource: %s\n\tDest: %s\n\tProtocol: %s\nIP: \n\tSource IP: %s\n\tDest Ip: %s\n\tVersion: %d\n\tTTL: %d\n\tProtocol: %s", eth.source, eth.dest, eth.proto, ip.source, ip.dest, ip.version, ip.ttl, ip.proto);
                if (strcmp(ip.proto, "TCP") == 0)
                {
                    struct tcphdr *tcp_header = (struct tcphdr *)(buf + (ip.ihl * 4));
                    printf("TCP packet: src port = %d, dst port = %d\n", ntohs(tcp_header->source), ntohs(tcp_header->dest));
                    // printf("\n\tSource Port: %d\n\tDest Port: %d", ip.source, ip.dest);
                }
                else if (strcmp(ip.proto, "UDP") == 0)
                {
                    struct udphdr *udp_header = (struct udphdr *)(buf + (ip.ihl * 4));
                    printf("UDP packet: src port = %d, dst port = %d\n", ntohs(udp_header->source), ntohs(udp_header->dest));
                    // printf("\n\tSource Port: %d\n\tDest Port: %d", ip.source, ip.dest);
                }
            } else if (strcmp(eth.proto, "ARP")) {
                wc_arp_p(buf, &arp);
                printf("\n ************************************* \nETH: \n\tSource: %s\n\tDest: %s\n\tProtocol: %s\nARP: \n\tHardware Type: %s\n\tProtocol Type: %s\n\tHardware Len: %d\n\tProtocol Len: %d\n\tOpcode: %s\n\tSender Mac: %s\n\tSender IP: %s\n\tTarget Mac: %s\n\tTarget IP: %s\n", eth.source, eth.dest, eth.proto, arp.hw_t, arp.p_t, arp.hw_len, arp.p_len, arp.opcode, arp.sender_mac, arp.sender_ip, arp.target_mac, arp.target_ip);
            }
        }
    }

    printf("Stage 3: close sock");
    close(sock);
    free(buf);

    return 0;
}
