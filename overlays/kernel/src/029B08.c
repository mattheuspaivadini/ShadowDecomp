/* KERNEL.XFF @ 0x029B08 (88 B) - Sg2SlotSetBasePan
 * Evidence: stores the base pan at +0x50, then flag 0x2000 (pan update). Slots are the 48 0xE0-byte records at .bss+0x97E30. The update flag is only raised when both remote words (+0x68, +0x6C) are valid (not -1); the nested-member form slot[i].remote.x gives the image's (i*0xE0+0x60)+base addressing. UNCONFIRMED: field names.
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
    int unk38;
    int unk3C;
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
void Sg2SlotSetBasePan(int i, int v) {
    slot[i].basePan = v;
    if (slot[i].remote.unk68 != -1 && slot[i].remote.unk6C != -1) {
        slot[i].flags |= 0x2000;
    }
}
