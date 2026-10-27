/* KERNEL.XFF @ 0x013948 (148 B) - iosDlRelease
 * Evidence: for both buffers, iosFree(buf[i]) then iosFree(base[i]) when non-null (each field read twice: the DL work block at .bss+0x1EAD8 is a volatile struct, see iosDlGetLayer). UNCONFIRMED: names.
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
void iosFree(void *p);

void iosDlRelease(void) {
    int i;

    for (i = 0; i < 2; i++) {
        if (D_kernel_bss_1EAD8.buf[i]) {
            iosFree(D_kernel_bss_1EAD8.buf[i]);
        }
        if (D_kernel_bss_1EAD8.base[i]) {
            iosFree(D_kernel_bss_1EAD8.base[i]);
        }
    }
}
