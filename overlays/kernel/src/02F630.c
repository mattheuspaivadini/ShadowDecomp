/* KERNEL.XFF @ 0x02F630 (160 B) - Sg2ExPcmOutputCtrl
 * Evidence: unless (mode & 3) == 3: bit 0 with the output idle (+4 bit 0 clear) clears +0x18 and, when the buffer (+0x1A4) and +0xC are set, Sg2StPcmStart(buf, +0x1A8 * 2); bit 1 Sg2StPcmStop(); then +4 = mode (PCM output block .bss+0x9BE20). int without a return value, as the input controls. UNCONFIRMED: field names.
 */
struct PcmOutput {
    char pad0[4];
    int status;
    char pad8[4];
    int unkC;
    char pad10[8];
    int unk18;
    char pad1C[0x1A4 - 0x1C];
    void *buf;
    int size;
};
extern struct PcmOutput D_kernel_bss_9BE20;
void Sg2StPcmStart(void *buf, int size);
void Sg2StPcmStop(void);

int Sg2ExPcmOutputCtrl(int mode) {
    if ((mode & 3) != 3) {
        if (mode & 1) {
            if (!(D_kernel_bss_9BE20.status & 1)) {
                D_kernel_bss_9BE20.unk18 = 0;
                if (D_kernel_bss_9BE20.buf && D_kernel_bss_9BE20.unkC) {
                    Sg2StPcmStart(D_kernel_bss_9BE20.buf, D_kernel_bss_9BE20.size * 2);
                }
            }
        }
        if (mode & 2) {
            Sg2StPcmStop();
        }
        D_kernel_bss_9BE20.status = mode;
    }
}
