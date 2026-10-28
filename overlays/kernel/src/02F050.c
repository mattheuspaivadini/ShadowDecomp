/* KERNEL.XFF @ 0x02F050 (40 B) - Sg2ExPcmInputGetLipFrame
 * Evidence: for ch < 4 returns word +0x14 of the 0x1D4-byte PCM record [ch] (.bss+0x9BFD8 array), else -1. UNCONFIRMED: field meaning beyond the symbol name.
 */
struct PcmInput {
    char pad0[0x14];
    int lip_frame;
    char pad18[0x1D0 - 0x18];
    int play_frame;
};
extern struct PcmInput D_kernel_bss_9BFD8[4];

int Sg2ExPcmInputGetLipFrame(unsigned int ch) {
    if (ch >= 4) {
        return -1;
    }
    return D_kernel_bss_9BFD8[ch].lip_frame;
}
