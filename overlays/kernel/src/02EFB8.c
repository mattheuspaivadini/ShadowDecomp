/* KERNEL.XFF @ 0x02EFB8 (148 B) - Sg2ExPcmInputCtrl
 * Evidence: for ch < 4 and (mode & 3) != 3: under DIntr/EIntr, mode bit 0 clears the record's +0x14 and +0x1D0 counters, then record +0 = mode (0x1D4-byte PCM input records at .bss+0x9BFD8). The int function without a return value keeps EIntr a jal (no sibling call). UNCONFIRMED: field names, return type.
 */
struct PcmInput {
    int status;
    char pad4[0x10];
    int lip_frame;
    char pad18[0x1D0 - 0x18];
    int play_frame;
};
extern struct PcmInput D_kernel_bss_9BFD8[4];
int DIntr(void);
int EIntr(void);

int Sg2ExPcmInputCtrl(unsigned int ch, int mode) {
    int intr;

    if (ch < 4 && (mode & 3) != 3) {
        intr = DIntr();
        if (mode & 1) {
            D_kernel_bss_9BFD8[ch].lip_frame = 0;
            D_kernel_bss_9BFD8[ch].play_frame = 0;
        }
        D_kernel_bss_9BFD8[ch].status = mode;
        if (intr) {
            EIntr();
        }
    }
}
