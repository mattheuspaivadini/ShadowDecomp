/* KERNEL.XFF @ 0x01FA58 (104 B) - Sg2DspEffectSetDepth
 * Evidence: the 16-bit depth (sign-extended argument) goes to halfwords +0xE and +0xC, the old +0xC is returned (lh); DIntr/EIntr bracket as in the other DSP setters.
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

int Sg2DspEffectSetDepth(int core, short depth) {
    int old;
    int intr = DIntr();

    old = D_kernel_bss_7F5C8[core].depthL;
    D_kernel_bss_7F5C8[core].depthR = depth;
    D_kernel_bss_7F5C8[core].depthL = depth;
    if (intr) {
        EIntr();
    }
    return old;
}
