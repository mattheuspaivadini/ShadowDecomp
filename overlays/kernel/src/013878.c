/* KERNEL.XFF @ 0x013878 (184 B) - iosDlPushLayer
 * Evidence: pushes the current layer on the 256-entry layer stack (.bss+0x1EB08, depth at .data+0x570); on overflow prints .rodata+0x1138 "dl layer stack overflow. %d->%d" with (current, new); then the iosDlSetLayer body is inlined (negative layer prints .rodata+0x1120, too large clamps to layerNum - 1). UNCONFIRMED: names.
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
extern char D_kernel_rodata_1138[];
int LoaderSysPrintf(const char *fmt, ...);

static inline void iosDlSetLayer(int layer) {
    if (layer < 0) {
        LoaderSysPrintf(D_kernel_rodata_1120);
    } else if (layer >= D_kernel_bss_1EAD8.layerNum) {
        layer = D_kernel_bss_1EAD8.layerNum - 1;
    }
    D_kernel_bss_1EAD8.layer = layer;
}

void iosDlPushLayer(int layer) {
    D_kernel_bss_1EB08[D_kernel_data_0570] = D_kernel_bss_1EAD8.layer;
    if (++D_kernel_data_0570 >= 256) {
        LoaderSysPrintf(D_kernel_rodata_1138, D_kernel_bss_1EAD8.layer, layer);
    }
    iosDlSetLayer(layer);
}
