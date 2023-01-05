#include "arp.h"

void wc_arp_p(const unsigned char *in, wc_arp *out)
{
    wc_arphdr *arp = (wc_arphdr *)(in + sizeof(wc_ethdr));
    // hardware type
    // if (arp->ar_hrd == ARPHRD_ETHER)
    //    out->hw_t = "ETHERNET";
    // else
    //     out->hw_t = "OTHER";
    out->hw_t = wc_format("%u", ntohs(arp->ar_hrd));
    // protocol type
    out->p_t = wc_format("%u", ntohs(arp->ar_pro));
    // hardware len
    out->hw_len = (uint8_t)arp->ar_hln;
    // protocol len
    out->p_len = (uint8_t)arp->ar_pln;
    // arp opcode
    switch (ntohs(arp->ar_op))
    {
    case ARPOP_REQUEST:
        out->opcode = "REQUEST";
    case ARPOP_REPLY:
        out->opcode = "REPLY";
    case ARPOP_NAK:
        out->opcode = "NAK";
    default:
        out->opcode = "OTHER";
    }
    // sender mac
    out->sender_mac = wc_format("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", arp->__ar_sha[0], arp->__ar_sha[1], arp->__ar_sha[2], arp->__ar_sha[3], arp->__ar_sha[4], arp->__ar_sha[5]);
    // sender ip
    out->sender_ip = wc_format("%u.%u.%u.%u", arp->__ar_sip[0], arp->__ar_sip[1], arp->__ar_sip[2], arp->__ar_sip[3]);
    // target mac
    out->target_mac = wc_format("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", arp->__ar_tha[0], arp->__ar_tha[1], arp->__ar_tha[2], arp->__ar_tha[3], arp->__ar_tha[4], arp->__ar_tha[5]);
    // target ip
    out->target_ip = wc_format("%u.%u.%u.%u", arp->__ar_tip[0], arp->__ar_tip[1], arp->__ar_tip[2], arp->__ar_tip[3]);
} // parse arp header
