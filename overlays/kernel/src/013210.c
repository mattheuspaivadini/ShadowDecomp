/* KERNEL.XFF @ 0x013210 (72 B) - iosGetPacketPtrPath1
 * Evidence: rounds the volatile packet pointer up to 16 bytes when misaligned (p - (p & 0xF) + 0x10), a volatile `pref 0,0x40(p)` asm, returns the pointer. DL work block at .bss+0x1EAD8 (volatile struct, see iosDlGetLayer). UNCONFIRMED: names.
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

char *iosGetPacketPtrPath1(void) {
    if ((unsigned int)D_kernel_bss_1EAD8.packet & 0xF) {
        D_kernel_bss_1EAD8.packet = D_kernel_bss_1EAD8.packet - ((unsigned int)D_kernel_bss_1EAD8.packet & 0xF) + 0x10;
    }
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(D_kernel_bss_1EAD8.packet));
    return D_kernel_bss_1EAD8.packet;
}
