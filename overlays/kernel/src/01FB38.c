/* KERNEL.XFF @ 0x01FB38 (96 B) - Sg2DspEffectSetDelay
 * Evidence: DIntr(); old = table[core].+0x10 (24-byte records at .bss+0x7F5C8); store the new value; EIntr() only if interrupts were enabled; returns old. UNCONFIRMED: field names.
 */
struct DspEffect {
    int volL;
    int volR;
    int unk8;
    short unkC;
    short unkE;
    int delay;
    int feedback;
};
extern struct DspEffect D_kernel_bss_7F5C8[2];
int DIntr(void);
int EIntr(void);

int Sg2DspEffectSetDelay(int core, int value) {
    int old;
    int intr = DIntr();

    old = D_kernel_bss_7F5C8[core].delay;
    D_kernel_bss_7F5C8[core].delay = value;
    if (intr) {
        EIntr();
    }
    return old;
}
