/* KERNEL.XFF @ 0x029640 (92 B) - Sg2SlotFindSlotClassCh
 * Evidence: like Sg2SlotFindSlotClass, also requiring +0x14 == ch. The 48 voice slots are 0xE0-byte records at .bss+0x97E30 (index * 7 * 32); field offsets come from the slot setters. UNCONFIRMED: field names.
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

int Sg2SlotFindSlotClassCh(int *out, int vab, int ch) {
    int n = 0;
    int i;

    for (i = 0; i < 48; i++) {
        if ((slot[i].flags & 1) && slot[i].cls == vab && slot[i].ch == ch) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
