/* KERNEL.XFF @ 0x02EF28 (140 B) - Sg2ExPcmInputClose
 * Evidence: for ch < 4: under DIntr/EIntr, Sg2ExPcmInputCtrl(ch, 2), free(record.buf at +8), then +4 and +8 cleared (0x1D4-byte PCM input records at .bss+0x9BFD8). int without a return value, as Sg2ExPcmInputCtrl. UNCONFIRMED: field names.
 */
struct PcmInput {
    int status;
    int unk4;
    void *buf;
    char padC[0x1D4 - 0xC];
};
extern struct PcmInput D_kernel_bss_9BFD8[4];
int DIntr(void);
int EIntr(void);
int Sg2ExPcmInputCtrl(unsigned int ch, int mode);
void free(void *p);

int Sg2ExPcmInputClose(unsigned int ch) {
    int intr;

    if (ch < 4) {
        intr = DIntr();
        Sg2ExPcmInputCtrl(ch, 2);
        free(D_kernel_bss_9BFD8[ch].buf);
        D_kernel_bss_9BFD8[ch].unk4 = 0;
        D_kernel_bss_9BFD8[ch].buf = 0;
        if (intr) {
            EIntr();
        }
    }
}
