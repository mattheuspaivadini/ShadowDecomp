/* KERNEL.XFF @ 0x01FBF8 (348 B) - Sg2DspEffectChange
 * Evidence: under DIntr/EIntr re-sends the effect settings of core [i] (0x18-byte records at .bss+0x7F5C8) through Sg2RemoteSend: 0xB mode (+8), 0x10 feedback and 0xF delay (sub-record at +0x10: +4/+0), 0xE depths (shorts +0xC/+0xE scaled * 0x7FFF / 0x7F), then clears flag 0x100 of +4 and sends 0xD (flag was set) or 0xC with the new flags; returns 0. The nested delay sub-record reproduces the (i*0x18 + 0x10) + (base + 4) addressing. UNCONFIRMED: names.
 */
struct DspDelay {
    int delay;
    int feedback;
};
struct DspCore {
    int unk0;
    unsigned int flags;
    int mode;
    short depth_l;
    short depth_r;
    struct DspDelay d;
};
extern struct DspCore D_kernel_bss_7F5C8[2];
int DIntr(void);
int EIntr(void);
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2DspEffectChange(int core) {
    int intr = DIntr();
    int dl = D_kernel_bss_7F5C8[core].depth_l * 0x7FFF / 0x7F;
    int dr = D_kernel_bss_7F5C8[core].depth_r * 0x7FFF / 0x7F;
    unsigned int flags;

    Sg2RemoteSend(0xB, core, D_kernel_bss_7F5C8[core].mode, 0);
    Sg2RemoteSend(0x10, core, D_kernel_bss_7F5C8[core].d.feedback, 0);
    Sg2RemoteSend(0xF, core, D_kernel_bss_7F5C8[core].d.delay, 0);
    Sg2RemoteSend(0xE, core, dl, dr);
    flags = D_kernel_bss_7F5C8[core].flags;
    D_kernel_bss_7F5C8[core].flags = flags & ~0x100;
    Sg2RemoteSend(flags & 0x100 ? 0xD : 0xC, core, flags & ~0x100, 0);
    if (intr) {
        EIntr();
    }
    return 0;
}
