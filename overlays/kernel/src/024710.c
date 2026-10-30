/* KERNEL.XFF @ 0x024710 (512 B) - func_024710
 * Evidence: MIDI controller dispatch for the DSP effect parameters. Message
 * pointer .bss+0x7F6CC (lbu [0]&0xF = channel, lbu [2] = value), module record
 * pointer .bss+0x7F6D0: the channel record is 0x70 B at module+0x2B0, and the
 * DSP effect parameters are 3 signed bytes at +0x64..+0x66 of that record
 * (module+0x314..0x316; the store proves the +0x314 base, the two `addu` at
 * 0x024744/0x024748 are the separate value store and parameter pointer).
 * value = msg[2], then mode (+0) selects core 0 / core 1 / Sg2ModSetParam,
 * type (+1) selects SetType/SetDepth/SetDelay/SetFeedBack/Change (0x7F).
 * Tail calls with `addiu sp,sp,0x10`; all five callees are the lane's named
 * Sg2DspEffect* setters, func_022308 is Sg2ModSetParam.
 * Size: Ghidra reported 484 B (it stops at 0x248F4, inside the case-2 tail
 * call); the real body ends at 0x24910 after `jr $ra` + delay -> 512 B.
 * Build: -G0 -g0 (also -G0 -fno-strict-aliasing -g0). Plain -G0 is 12 B short:
 * the -g0 delayed-branch scheduler is what turns the case-2 call into the
 * image's tail `j Sg2ModSetParam` with the `nop` delay slot.
 * UNCONFIRMED: struct/field names, block id 0x800, D_kernel_bss_7F6C8 (module id).
 */
struct Sg2DspParam {
    signed char mode;
    signed char type;
    signed char value;
    char pad[0x0C - 3];
};
struct Sg2ModChan {
    char pad0[0x64];
    struct Sg2DspParam dsp;
    char pad70[0x70 - 0x64 - 0x0C];
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
extern int D_kernel_bss_7F6C8;
int Sg2DspEffectSetType(int core, int value);
int Sg2DspEffectSetDepth(int core, int value);
int Sg2DspEffectSetDelay(int core, int value);
int Sg2DspEffectSetFeedBack(int core, int value);
int Sg2DspEffectChange(int core);
int Sg2ModSetParam(int id, int param, int value, int unk);

void func_024710(void) {
    unsigned char *msg = D_kernel_bss_7F6CC;
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = msg[0] & 0xF;
    struct Sg2DspParam *p;

    m->ch[ch].dsp.value = msg[2];
    p = &m->ch[ch].dsp;
    switch (p->mode) {
    case 0:
        switch (p->type) {
        case 0: Sg2DspEffectSetType(0, p->value); break;
        case 1: Sg2DspEffectSetDepth(0, p->value); break;
        case 2: Sg2DspEffectSetDelay(0, p->value); break;
        case 3: Sg2DspEffectSetFeedBack(0, p->value); break;
        case 0x7F: Sg2DspEffectChange(0); break;
        }
        break;
    case 1:
        switch (p->type) {
        case 0: Sg2DspEffectSetType(1, p->value); break;
        case 1: Sg2DspEffectSetDepth(1, p->value); break;
        case 2: Sg2DspEffectSetDelay(1, p->value); break;
        case 3: Sg2DspEffectSetFeedBack(1, p->value); break;
        case 0x7F: Sg2DspEffectChange(1); break;
        }
        break;
    case 2:
        if (p->type == 0) {
            Sg2ModSetParam(D_kernel_bss_7F6C8, 0x800, p->value, 0);
        }
        break;
    }
}
