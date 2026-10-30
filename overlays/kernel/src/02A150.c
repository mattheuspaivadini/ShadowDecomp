/* KERNEL.XFF @ 0x02A150 (328 B) - Sg2SlotSetLfoVolDepth
 * Evidence: v == 0 gives f = 0.0f, otherwise f = (float)v / 127.0f (the
 * constant is `lui $at,0x42FE` + `mtc1`, i.e. 0x42FE0000 = 127.0f). The
 * float -> unsigned int conversion shows the classic R5900 clamp
 * (`c.le.s` against 0x4F000000 = 2^31, `sub.s`, `or 0x80000000`) and lands in
 * slot+0x94. Flag 0x800 is set only when the new value is non-zero *and*
 * slot+0x90 read back as unsigned (`lw` + bltz/srl/andi = unsigned -> float) is
 * non-zero; otherwise it is cleared (`and` with ~0x801). The 48 voice slots are
 * 0xE0-byte records at .bss+0x97E30 (struct from 029D08.c, whose pad90[0xC] is
 * split here into the two LFO-volume words + one unknown at +0x98). `-g0` is
 * required (delayed-branch scheduling). UNCONFIRMED: field/parameter names.
 */
struct Sg2Remote {
    int ssa;
    unsigned short adsr1;
    unsigned short adsr2;
    int unk68;
    int unk6C;
};
struct Sg2Lfo {
    int unk0;
    int *tbl;
    int *cur;
    int *end;
};
struct Sg2Env {
    int *cur;
    int *end;
    float target;
    float time;
};
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int unk08;
    int cls;
    int vab;
    int ch;
    int unk18;
    int group;
    char pad20[0x14];
    int masTune;
    char pad38[8];
    int seMasVol;
    int baseVol;
    int vol;
    int masPan;
    int basePan;
    int pan;
    int bendRange;
    int bendValue;
    struct Sg2Remote remote;
    int directPitch;
    short volPhase1;
    short volPhase2;
    char pad78[8];
    struct Sg2Lfo lfoPitch;
    unsigned int lfoVolSpeed;
    unsigned int lfoVolDepth;
    int unk98;
    int *lfoVolTbl;
    struct Sg2Env vol2;
    int unkB0;
    float panTarget;
    float panTime;
    int unkBC;
    float pitchTarget;
    float pitchTime;
    char padC8[0x18];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
#define slot D_kernel_bss_97E30

void Sg2SlotSetLfoVolDepth(int i, int v) {
    float f;

    if (v != 0) {
        f = v;
        f /= 127.0f;
    } else
        f = 0.0f;
    slot[i].lfoVolDepth = f;
    if (f != 0.0 && (float)slot[i].lfoVolSpeed != 0.0f)
        slot[i].flags |= 0x800;
    else
        slot[i].flags &= ~0x800;
}
