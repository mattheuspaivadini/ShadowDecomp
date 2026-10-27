/* KERNEL.XFF @ 0x01F9F0 (100 B) - Sg2DspEffectSetType
 * Evidence: field +4 (type): DIntr(); old value read and the new one stored in the 24-byte DSP record [core] at .bss+0x7F5C8; EIntr() only if interrupts were enabled; returns old. UNCONFIRMED: field names.
 */
struct DspEffect {
    int volL;
    int type;
    int endAdr;
    short depthL;
    short depthR;
    int delay;
    int feedback;
};
extern struct DspEffect D_kernel_bss_7F5C8[2];
int DIntr(void);
int EIntr(void);

int Sg2DspEffectSetType(int core, int value) {
    int old;
    int intr = DIntr();

    old = D_kernel_bss_7F5C8[core].type;
    D_kernel_bss_7F5C8[core].type = value;
    if (intr) {
        EIntr();
    }
    return old;
}
