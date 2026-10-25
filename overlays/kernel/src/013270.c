/* KERNEL.XFF @ 0x013270 (36 B) - iosAllocPacketPtrPath1
 * Evidence: returns the old packet pointer and advances it by size (packet read twice: volatile); a volatile `pref 0,0x40(p)` asm prefetches the next line. DL work block at .bss+0x1EAD8 accessed as a volatile struct (every field
 * goes through `lui/addiu` + offset with no relocation on the load, and the
 * `jr` slot stays a nop). Layout used: base[2] +0, buf[2] +8, packet +0x10,
 * layerNum +0x14, workBufId +0x18, layer +0x1C. UNCONFIRMED: names/layout.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
};
extern volatile struct DLWork D_kernel_bss_1EAD8;

char *iosAllocPacketPtrPath1(int size) {
    char *p = D_kernel_bss_1EAD8.packet;

    D_kernel_bss_1EAD8.packet += size;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(p));
    return p;
}
