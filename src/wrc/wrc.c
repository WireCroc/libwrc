#include "wrc.h"

void wrc_default(wrc* w) {
    // todo(stdout, "Impl Wrc Default VL", 0);
    w->fd = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
    if (w->fd < 0) {
        fprintf(stderr, "Socket Error\n");
        exit(w->fd);
    }
    w->recvl = 0;
    w->recvn = 0;
    w->iface = (wc_iface) {0};
    w->flag = 0;
    w->ign_pa = PA_NULL;
} // creating a socket

int8_t wrc_setopts(wrc* w, wc_iface ifc, pa ignore_p, int8_t flag) {
    // todo(stdout, "set options for wrc", 0);
    int stat = setsockopt(w->fd, SOL_SOCKET, SO_BINDTODEVICE, ifc.name, strlen(ifc.name));
    if (stat != 0)
        return ERR;

    w->recv = (unsigned char*) malloc(ifc.mtu);
    memset(w->recv, 0, ifc.mtu);
    w->iface = ifc;
    w->ign_pa = ignore_p;
    w->flag = flag;
    return OK;
} // setting options

void wrc_destroy(wrc *w) {
    // todo(stdout, "Free wrc and trash", 0);
    shutdown(w->fd, 0);
    close(w->fd);
    if (w->recv > 0)
       free(w->recv);
} // closing a socket and freeing memory

int8_t wrc_cap(wrc* w, uint8_t f, void (*cb)(wc_pa, FILE*)) {
    // todo(stdout, "Run sniffer in loop", 0);
    FILE* fp;
    if (f != 0) {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);

      fp = fopen(wc_format("%d-%02d-%02d-%02d-%02d-%02d.wrc", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec), "w");
    }

    do {
        wc_pa pa = wrc_get_packets(w);
        if (pa.p[0] == PA_NULL)
            CAPL = 0;
        cb(pa, f != 0 ? fp : stdout);
    } while (CAPL);
    fclose(fp);
    
    return OK;
} // capturing packets

void DEFAULT_CAP(wc_pa pa, FILE* fp) {
    for (int i = 0; i < MAX_PA; i++) {
        if (pa.p[i] == PA_ETH) {            
            fprintf(fp, "Ethernet\n\tMac Src: %s\t|\tMac Dst: %s\n", pa.eth.source, pa.eth.dest);
        } else if (pa.p[i] == PA_ARP) {
            fprintf(fp, "ARP\n\tHardware Type: %s\t|\tProtocol Type: %s\n\tHardware Address Length: %d\t|\tProtocol Address Length: %d\n\tOpcode: %s\n\tSender Mac: %s\n\tTarget Mac: %s\n\tSender IP: %s\n\tTarget IP: %s\n", pa.arp.hw_t, pa.arp.p_t, pa.arp.hw_len, pa.arp.p_len, pa.arp.opcode, pa.arp.sender_mac, pa.arp.target_mac, pa.arp.sender_ip, pa.arp.target_ip);
        } else if (pa.p[i] == PA_IP) {
            fprintf(fp, "IP\n\tSrc Address: %s\t|\tDst Address: %s\n", pa.ip.source, pa.ip.dest);
        } else if (pa.p[i] == PA_TCP) {
            fprintf(fp, "TCP\n\tWindow: %u\t|\tACK Sequence: %u\n\tSequence: %u\n\tSrc Port: %d\t|\tDst Port: %d\n", pa.tcp.window, pa.tcp.ack_sequence, pa.tcp.sequence, pa.tcp.source, pa.tcp.dest);
        } else if (pa.p[i] == PA_UDP) {
            fprintf(fp, "UDP\n\tSrc Port: %d\t|\tDst Port: %d\n", pa.udp.source, pa.udp.dest);
        } else if (pa.p[i] == PA_NULL && (i + 1 == MAX_PA || i == MAX_PA - 2)) {
            fprintf(fp, "\t_________________________\n");
        }
    }
} // default capture function

wc_iflist wrc_get_interfaces(void) {
    // todo(stdout, "Get all Interfaces", 0);
    struct ifaddrs *ifa, *ifaa; int idx = 0; int check = 0;
    wc_iflist res;
    memset(res.ifc, 0, MAX_IFACE * sizeof(wc_iface));
    getifaddrs(&ifa);
    res.len = 0;
    
    for (ifaa = ifa; ifaa != NULL; ifaa = ifaa->ifa_next) {
        for (int i = 0; i < MAX_IFACE; i++) {
            if (strcmp(res.ifc[i].name, ifaa->ifa_name) == 0) {
                check = 1;
                break;
            }
        }
        if (check != 1) {
            strncpy(res.ifc[idx].name, ifaa->ifa_name, strlen(ifaa->ifa_name));
            res.ifc[idx].flag = ifaa->ifa_flags;
            res.ifc[idx].mtu = 1500;
            res.len++;
        }
        check = 0; idx++;
    }

    freeifaddrs(ifa);
    return res;
} //function for getting interfaces

// private fucs
wc_pa wrc_get_packets(wrc* w) {
    // todo(stdout, "Get packets for wrc", 0);
    wc_pa res;
    wc_pa_set(&res);
    int size = sizeof(w->saddr);
    w->recvl = recvfrom(w->fd, w->recv, w->iface.mtu, 0, &w->saddr, (socklen_t *)&size);

    if (w->recvl < 0) {
        fprintf(stderr, "Cant Get Packets\n");
        return (wc_pa) {.p[0] = PA_NULL};
    } else {
        wc_eth_p(w->recv, &res.eth);
        res.p[0] = PA_ETH;
        if (res.eth.proto == ARP) {
            wc_arp_p(w->recv, &res.arp);
            res.p[1] = PA_ARP;
            
            return res;
        } else if (res.eth.proto == IP) {
            wc_ip_p(w->recv, &res.ip);
            res.p[1] = PA_IP;
            if (res.ip.proto == TCP) {
                wc_tcp_p(w->recv, &res.tcp, res.ip.ihl);
                res.p[2] = PA_TCP;
                
                return res;
            } else if (res.ip.proto == UDP) {
                wc_udp_p(w->recv, &res.udp, res.ip.ihl);
                res.p[2] = PA_UDP;
                
                return res;
            }
        }
    }
    return res;
} // getting packets and returning them

void wc_pa_set(wc_pa *p) {
    p->eth = (wc_eth) {0};
    p->arp = (wc_arp) {0};
    p->ip = (wc_ip) {0};
    p->tcp = (wc_tcp) {0};
    p->udp = (wc_udp) {0};
    memset(p->p, 0, sizeof(p->p));
} // declaring packet struct
