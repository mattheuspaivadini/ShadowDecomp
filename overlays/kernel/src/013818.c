/* KERNEL.XFF @ 0x013818 (96 B) - iosDlSetLayer
 * Evidence: a negative layer only prints .rodata+0x1120 (LoaderSysPrintf) and is still stored; a layer >= layerNum is clamped to layerNum - 1; stored to +0x1C. DL work block at .bss+0x1EAD8 (volatile struct, see iosDlGetLayer). UNCONFIRMED: names.
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
extern char D_kernel_rodata_1120[];
int LoaderSysPrintf(const char *fmt, ...);

void iosDlSetLayer(int layer) {
    if (layer < 0) {
        LoaderSysPrintf(D_kernel_rodata_1120);
    } else if (layer >= D_kernel_bss_1EAD8.layerNum) {
        layer = D_kernel_bss_1EAD8.layerNum - 1;
    }
    D_kernel_bss_1EAD8.layer = layer;
}
