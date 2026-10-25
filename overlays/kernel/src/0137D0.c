/* KERNEL.XFF @ 0x0137D0 (48 B) - iosDlGetEndAdrs
 * Evidence: returns base[workBufId] + (.data+0x56C)*16 - 0x1000. DL work block at .bss+0x1EAD8 accessed as a volatile struct (every field
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

extern int D_kernel_data_056C;
char *iosDlGetEndAdrs(void) {
    return D_kernel_bss_1EAD8.base[D_kernel_bss_1EAD8.workBufId] + D_kernel_data_056C * 16 - 0x1000;
}
