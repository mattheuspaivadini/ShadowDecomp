/* KERNEL.XFF @ 0x02A000 (336 B) - Sg2SlotSetLfoVolSpeed
 * Evidence: twin of 0x02A150 (Sg2SlotSetLfoVolDepth): v == 0 gives f = 0.0f,
 * otherwise f = (float)v / 6.35f (lui 0x40CB + ori 0x3333 = 0x40CB3333).
 * The float -> unsigned int conversion (2^31 clamp, or 0x80000000) stores into
 * slot+0x90; flag 0x800 is set only when the new speed and slot+0x94 (read as
 * unsigned and converted to float) are both non-zero. Same 0xE0-byte slot
 * records at .bss+0x97E30; `-g0` needed. UNCONFIRMED: field/parameter names.
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

void Sg2SlotSetLfoVolSpeed(int i, int v) {
    float f;

    if (v != 0) {
        f = v;
        f /= 6.35f;
    } else
        f = 0.0f;
    slot[i].lfoVolSpeed = f;
    if (f != 0.0 && (float)slot[i].lfoVolDepth != 0.0f)
        slot[i].flags |= 0x800;
    else
        slot[i].flags &= ~0x800;
}
