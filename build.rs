extern crate cc;

fn main() {
    cc::Build::new()
        .file("libwrc/wrc/wrc.c")
        .file("libwrc/eth/eth.c")
        .file("libwrc/arp/arp.c")
        .file("libwrc/ip/ip.c")
        .file("libwrc/tcp/tcp.c")
        .file("libwrc/udp/udp.c")
        .file("libwrc/utils/utils.c")
        .compile("libwrc");
}
