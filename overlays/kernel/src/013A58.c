/* KERNEL.XFF @ 0x013A58 (104 B) - iosDlCheckSize
 * Evidence: end = base[workBufId] + .data+0x56C * 16 - 0x1000; the packet pointer is rounded up to 16 bytes, prefetched (volatile pref asm), and end - packet is returned. DL work block at .bss+0x1EAD8 (volatile struct). UNCONFIRMED: names.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
    char group[2][4];
    int lockNum[2];
};
extern volatile struct DLWork D_kernel_bss_1EAD8;
extern int D_kernel_data_056C;

int iosDlCheckSize(void) {
    char *end = D_kernel_bss_1EAD8.base[D_kernel_bss_1EAD8.workBufId] + D_kernel_data_056C * 16 - 0x1000;

    if ((unsigned int)D_kernel_bss_1EAD8.packet & 0xF) {
        D_kernel_bss_1EAD8.packet = D_kernel_bss_1EAD8.packet - ((unsigned int)D_kernel_bss_1EAD8.packet & 0xF) + 0x10;
    }
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(D_kernel_bss_1EAD8.packet));
    return end - D_kernel_bss_1EAD8.packet;
}
