/* KERNEL.XFF @ 0x012F28 (240 B) - iosDlPopLayer
 * Evidence: pops the layer stack (depth at .data+0x570, entries at .bss+0x1EB08); on underflow prints .rodata+0x1160 "dl layer stack error. %d->%d" with (current, popped); then the iosDlSetLayer body is inlined on the popped value, which is re-read and returned. UNCONFIRMED: names.
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
extern int D_kernel_bss_1EB08[256];
extern int D_kernel_data_0570;
extern char D_kernel_rodata_1120[];
extern char D_kernel_rodata_1160[];
int LoaderSysPrintf(const char *fmt, ...);

static inline void iosDlSetLayer(int layer) {
    if (layer < 0) {
        LoaderSysPrintf(D_kernel_rodata_1120);
    } else if (layer >= D_kernel_bss_1EAD8.layerNum) {
        layer = D_kernel_bss_1EAD8.layerNum - 1;
    }
    D_kernel_bss_1EAD8.layer = layer;
}

int iosDlPopLayer(void) {
    if (--D_kernel_data_0570 < 0) {
        LoaderSysPrintf(D_kernel_rodata_1160, D_kernel_bss_1EAD8.layer, D_kernel_bss_1EB08[D_kernel_data_0570]);
    }
    iosDlSetLayer(D_kernel_bss_1EB08[D_kernel_data_0570]);
    return D_kernel_bss_1EB08[D_kernel_data_0570];
}
