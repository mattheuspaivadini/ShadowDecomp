/* KERNEL.XFF @ 0x013AE8 (40 B) - iosAllocPacketPtrPath1UnCachedA
 * Evidence: returns packet | 0x30000000 (the uncached-accelerated segment) and advances packet by size. DL work block at .bss+0x1EAD8 accessed as a volatile struct (every field
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

char *iosAllocPacketPtrPath1UnCachedA(int size) {
    char *p = (char *)((unsigned int)D_kernel_bss_1EAD8.packet | 0x30000000);

    D_kernel_bss_1EAD8.packet += size;
    return p;
}
