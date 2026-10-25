/* KERNEL.XFF @ 0x02F518 (96 B) - Sg2ExPcmOutputClose
 * Evidence: DIntr(); the static at .text+0x2F630 (2); takes the buffer pointer at .bss+0x9BE2C and clears it; EIntr() only if interrupts were on; free(buf); returns 0. UNCONFIRMED: names.
 */
struct PcmOutput {
    int unk0;
    int unk4;
    int unk8;
    void *buf;
};
extern struct PcmOutput D_kernel_bss_9BE20;
int DIntr(void);
int EIntr(void);
void func_02F630(int mode);
void free(void *p);

int Sg2ExPcmOutputClose(void) {
    int intr = DIntr();
    void *buf;

    func_02F630(2);
    buf = D_kernel_bss_9BE20.buf;
    D_kernel_bss_9BE20.buf = 0;
    if (intr) {
        EIntr();
    }
    free(buf);
    return 0;
}
