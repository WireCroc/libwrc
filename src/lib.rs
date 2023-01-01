use libc;

pub const OK: u8 = 0;
pub const ERR: u8 = 1;

pub const MAX_PA: usize = 3;
pub const MAX_IFACE: usize = 10;
pub const MAX_IFNAME: usize = 16;

#[allow(non_camel_case_types)]
#[repr(C)]
pub enum pa {
    PA_NULL = 0,
    PA_IP,
    PA_ARP,
    PA_TCP,
    PA_UDP,
    PA_ETH
}

#[allow(non_camel_case_types)]
#[repr(C)]
pub struct wc_eth {
    source: *mut libc::c_uchar,
    dest: *mut libc::c_uchar,
    proto: libc::c_ushort
}

#[allow(non_camel_case_types)]
#[repr(C)]
pub struct wc_arp {
    hw_t: *mut libc::c_char,
    p_t: *mut libc::c_char,
    hw_len: libc::c_uchar,
    p_len: libc::c_uchar,
    opcode: *mut libc::c_char,
    sender_mac: *mut libc::c_char,
    sender_ip: *mut libc::c_char,
    target_mac: *mut libc::c_char,
    target_ip: *mut libc::c_char,
}

#[allow(non_camel_case_types)]
#[repr(C)]
pub struct wc_ip {
    version: libc::c_uchar,
    ttl: libc::c_int,
    ihl: libc::c_int,
    tos: libc::c_ushort,
    tl: libc::c_longlong,
    ident: libc::c_short,
    hchs: libc::c_int,
    source: *mut libc::c_uchar,
    dest: *mut libc::c_uchar,
    proto: libc::c_uchar
}

#[allow(non_camel_case_types)]
#[derive(Debug)]
#[repr(C)]
pub struct wc_iface {
    name: [libc::c_char; MAX_IFNAME],
    mtu: libc::c_ulonglong,
    flag: libc::c_uchar
}

#[allow(non_camel_case_types)]
#[derive(Debug)]
#[repr(C)]
pub struct wc_iflist {
    ifc: [wc_iface; MAX_IFACE],
    len: libc::c_uchar
}

extern "C" {
    pub fn wrc_get_interfaces() -> wc_iflist;
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn it_works() {
        let ifc: wc_iflist = unsafe { wrc_get_interfaces() };
        println!("{:?}", ifc);
        assert_eq!(ifc.len, 3)
    }
}
