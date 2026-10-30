/* KERNEL.XFF @ 0x02A298 (60 B) - Sg2SlotSetTimeVolParam
 * Evidence: writes vol2.time (f12 -> +0xAC) and vol2.target (f13 -> +0xA8), then sets flag 0x20; signature order follows the argument registers. The 48 voice slots are 0xE0-byte records at
 * .bss+0x97E30 (struct from 029D08.c). Flag update is a single
 * read/or/store of the slot flags word. UNCONFIRMED: field names.
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
    char pad90[0xC];
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

void Sg2SlotSetTimeVolParam(int i, float time, float target) {
    slot[i].vol2.time = time;
    slot[i].vol2.target = target;
    slot[i].flags |= 0x20;
}
