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
}

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
}

void wrc_destroy(wrc *w) {
    // todo(stdout, "Free wrc and trash", 0);
    shutdown(w->fd, 0);
    close(w->fd);
    if (w->recv > 0)
       free(w->recv);
}

int8_t wrc_run_loop(wrc* w, void (*cb)(wrc*)) {
    todo(stdout, "Run sniffer in loop", 0);
}

int8_t wrc_run_(wrc *w) {
    todo(stdout, "Run sniffer without loop", 0);
}

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
}

// private fucs
wc_pa wrc_get_packets(wrc* w) {
    // todo(stdout, "Get packets for wrc", 0);
    wc_pa res;
    wc_pa_set(&res);
    int size = sizeof(w->saddr);
    w->recvl = recvfrom(w->fd, w->recv, w->iface.mtu, 0, &w->saddr, (socklen_t *)&size);

    if (w->recvl < 0) {
        fprintf(stderr, "Cant Get Packets\n");
        exit(1);
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
}

void wc_pa_set(wc_pa *p) {
    memset(p->p, 0, MAX_PA);
}
