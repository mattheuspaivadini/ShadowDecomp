/* KERNEL.XFF @ 0x01FD80 (144 B) - Sg2DspSetMasterVolume
 * Evidence: under DIntr/EIntr, stores l as the core's master volume (.bss+0x7F5C8 + core * 0x18, the field Sg2DspGetMasterVolume reads) and posts Sg2RemoteSend(6, core, l, r); EIntr is a sibling call, so the function returns void. UNCONFIRMED: parameter names.
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
int Sg2RemoteSend(int cmd, int a, int b, int c);

void Sg2DspSetMasterVolume(int core, int l, int r) {
    int intr = DIntr();

    D_kernel_bss_7F5C8[core].volL = l;
    Sg2RemoteSend(6, core, l, r);
    if (intr) {
        EIntr();
    }
}
