#include "wrc.h"

void wrc_default(wrc* w) {
    // todo(stdout, "Impl Wrc Default VL", 0);
    w->fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    w->recvl = 0;
    w->recvn = 0;
    w->iface = malloc(sizeof(wc_iface));
    w->saddr = malloc(sizeof(struct sockaddr));
    memset(w->iface, 0, sizeof(wc_iface));
    memset(w->saddr, 0, sizeof(struct sockaddr));
}

int8_t wrc_setopts(wrc* w, char* ifname, pa ignore_p, int8_t flag) {
    // todo(stdout, "set options for wrc", 0);
    
}

void wrc_destroy(wrc *w) {
    // todo(stdout, "Free wrc and trash", 0);
    shutdown(w->fd, 0);
    close(w->fd);
    free(w->iface);
    free(w->saddr);
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
    res.ifc = malloc(MAX_IFACE * sizeof(wc_iface));
    memset(res.ifc, 0, MAX_IFACE * sizeof(wc_iface));
    getifaddrs(&ifa);

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
void wrc_get_packets(wrc* w) {
    todo(stdout, "Get packets for wrc", 0);
}
