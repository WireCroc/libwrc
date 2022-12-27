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

int wrc_setopts(wrc* w, char* ifname, pa p, int8_t flag) {
    todo(stdout, "set options for wrc", 0);
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

int wrc_run_loop(wrc* w, void (*cb)(wrc*)) {
    todo(stdout, "Run sniffer in loop", 0);
}

int wrc_run_(wrc *w) {
    todo(stdout, "Run sniffer without loop", 0);
}

// private fucs
void wrc_get_packets(wrc* w) {
    todo(stdout, "Get packets for wrc", 0);
}
