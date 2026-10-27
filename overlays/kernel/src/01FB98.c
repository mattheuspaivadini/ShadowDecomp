/* KERNEL.XFF @ 0x01FB98 (96 B) - Sg2DspEffectSetFeedBack
 * Evidence: same as Sg2DspEffectSetDelay for the field at +0x14. UNCONFIRMED: field names.
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

int Sg2DspEffectSetFeedBack(int core, int value) {
    int old;
    int intr = DIntr();

    old = D_kernel_bss_7F5C8[core].feedback;
    D_kernel_bss_7F5C8[core].feedback = value;
    if (intr) {
        EIntr();
    }
    return old;
}
