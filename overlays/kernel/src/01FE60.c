/* KERNEL.XFF @ 0x01FE60 (60 B) - Sg2DspInit
 * Evidence: clears words +0/+4/+0x10/+0x14 and halfwords +0xC/+0xE of the two 24-byte DSP records at .bss+0x7F5C8; returns 0. UNCONFIRMED: layout.
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

int Sg2DspInit(void) {
    struct DspEffect *e = D_kernel_bss_7F5C8;
    int i;

    for (i = 1; i >= 0; i--, e++) {
        e->volL = 0;
        e->volR = 0;
        e->unkC = 0;
        e->unkE = 0;
        e->delay = 0;
        e->feedback = 0;
    }
    return 0;
}
