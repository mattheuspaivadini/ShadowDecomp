/* KERNEL.XFF @ 0x01FAC0 (120 B) - Sg2DspEffectSetDepth2
 * Evidence: +0xE = r, old = +0xC, +0xC = l (both 16-bit, sign-extended), under DIntr/EIntr; returns old.
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

int Sg2DspEffectSetDepth2(int core, short l, short r) {
    int old;
    int intr = DIntr();

    D_kernel_bss_7F5C8[core].depthR = r;
    old = D_kernel_bss_7F5C8[core].depthL;
    D_kernel_bss_7F5C8[core].depthL = l;
    if (intr) {
        EIntr();
    }
    return old;
}
