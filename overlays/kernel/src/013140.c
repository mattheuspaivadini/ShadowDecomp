/* KERNEL.XFF @ 0x013140 (116 B) - iosUsedPacketBufferSize
 * Evidence: (float)(unsigned)(packet - base[workBufId]) / (float)(.data+0x56C * 16) (GCC's unsigned-to-float sequence). DL work block at .bss+0x1EAD8 (volatile struct). UNCONFIRMED: names.
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

float iosUsedPacketBufferSize(void) {
    return (float)(unsigned int)(D_kernel_bss_1EAD8.packet - D_kernel_bss_1EAD8.base[D_kernel_bss_1EAD8.workBufId])
        / (float)(D_kernel_data_056C * 16);
}
