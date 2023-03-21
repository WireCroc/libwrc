#include "wrc.h"

static uint8_t CAPL = 1;
static wc_err WC_ERROR = {0};

void wrc_default(wrc* w) {
    // todo(stdout, "Impl Wrc Default VL", 0);
    if (geteuid())
        wrc_error((wc_err) {.code = ERR_SUDO, .msg = "Error: please run program with sudo\n"});
    
    w->fd = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
    if (w->fd < 0) {
        fprintf(stderr, "Error: failed init socket\n");
    }
        
    w->recvl = 0;
    w->recvn = 0;
    w->iface = (wc_iface) {0};
    w->flag = 0;
    w->ign_pa = PA_NULL;
} // creating a socket

wc_err wrc_error(wc_err err) {
    if (ERR_NULL != err.code)
        WC_ERROR = err;
    
    return WC_ERROR;
}

int8_t wrc_setopts(wrc* w, wc_iface ifc, pa ignore_p, int8_t flag) {
    // todo(stdout, "set options for wrc", 0);
    int stat = setsockopt(w->fd, SOL_SOCKET, SO_BINDTODEVICE, ifc.name, strlen(ifc.name));
    if (stat != 0) {
        wrc_error((wc_err) {.code = ERR_SETSOCK, .msg = "Error: failed setopts socket"});
        return ERR_SETSOCK;
    }

    w->recv = (unsigned char*) malloc(ifc.mtu);
    memset(w->recv, 0, ifc.mtu);
    w->iface = ifc;
    w->ign_pa = ignore_p;
    w->flag = flag;
    return WC_OK;
} // setting options

void wrc_destroy(wrc *w) {
    // todo(stdout, "Free wrc and trash", 0);
    shutdown(w->fd, 0);
    close(w->fd);
    if (w->recv > 0)
       free(w->recv);
} // closing a socket and freeing memory

int8_t wrc_cap(wrc* w, uint8_t f, wc_pa* cp, void (*cb)(wc_pa, FILE*)) {
    // todo(stdout, "Run sniffer in loop", 0);
    FILE* fp;
    if (f != 0) {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);

      fp = fopen(wc_format("%d-%02d-%02d-%02d-%02d-%02d.wrc", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec), "w");
    }

    do {
        wc_pa pa = wrc_get_packets(w);
        if (cp != NULL)
            cp = &pa;
        
        if (pa.p[0] == PA_NULL)
            CAPL = 0;
        cb(pa, f != 0 ? fp : stdout);
    } while (CAPL);
    fclose(fp);
    
    return WC_OK;
} // capturing packets

void DEFAULT_CAP(wc_pa pa, FILE* fp) {
    wc_ip* tip = (wc_ip*)malloc(sizeof(wc_ip));
    for (int i = 0; i < MAX_PA; i++) {
        if (pa.p[i] == PA_ETH) {
            fprintf(fp, "Ethernet\n\tMac Src: %s\t|\tMac Dst: %s\n", pa.pack.source, pa.pack.dest);
        } else if (pa.p[i] == PA_ARP) {
            wc_arp* arp = (wc_arp *)pa.pack.pl;
            fprintf(fp, "ARP\n\tHardware Type: %s\t|\tProtocol Type: %s\n\tHardware Address Length: %d\t|\tProtocol Address Length: %d\n\tOpcode: %s\n\tSender Mac: %s\n\tTarget Mac: %s\n\tSender IP: %s\n\tTarget IP: %s\n", arp->hw_t, arp->p_t, arp->hw_len, arp->p_len, arp->opcode, arp->sender_mac, arp->target_mac, arp->sender_ip, arp->target_ip);
        } else if (pa.p[i] == PA_IP) {
            tip = (wc_ip*)pa.pack.pl;
            fprintf(fp, "IP\n\tSrc Address: %s\t|\tDst Address: %s\n", tip->source, tip->dest);
        } else if (pa.p[i] == PA_TCP) {
            wc_tcp* tcp = (wc_tcp*)tip->pl;
            fprintf(fp, "TCP\n\tWindow: %u\t|\tACK Sequence: %u\n\tSequence: %u\n\tSrc Port: %d\t|\tDst Port: %d\n", tcp->window, tcp->ack_sequence, tcp->sequence, tcp->source, tcp->dest);
        } else if (pa.p[i] == PA_UDP) {
            wc_udp* udp = (wc_udp*)tip->pl;
            fprintf(fp, "UDP\n\tSrc Port: %d\t|\tDst Port: %d\n", udp->source, udp->dest);
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
        wc_eth_p(w->recv, &res.pack);
        res.p[0] = PA_ETH;
        if (res.pack.proto == ARP) {
            wc_arp* arp = (wc_arp*)malloc(sizeof(wc_arp));
            wc_arp_p(w->recv, arp, &res.pack);
            res.p[1] = PA_ARP;
            
            return res;
        } else if (res.pack.proto == IP) {
            wc_ip* ip = (wc_ip*)malloc(sizeof(wc_ip));
            wc_ip_p(w->recv, ip, &res.pack);
            res.p[1] = PA_IP;
            if (ip->proto == TCP) {
                wc_tcp* tcp = (wc_tcp*)malloc(sizeof(wc_tcp));
                wc_tcp_p(w->recv, tcp, ip->ihl, ip);
                res.p[2] = PA_TCP;
                
                return res;
            } else if (ip->proto == UDP) {
                wc_udp* udp = (wc_udp*)malloc(sizeof(wc_udp));
                wc_udp_p(w->recv, udp, ip->ihl, ip);
                res.p[2] = PA_UDP;
                
                return res;
            }
        }
    }
    return res;
} // getting packets and returning them

void wc_pa_set(wc_pa *p) {
    memset(p->p, 0, sizeof(p->p));
} // declaring packet struct
