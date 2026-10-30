/* KERNEL.XFF @ 0x029D88 (56 B) - Sg2SlotSetVolPhase   [MATCH: -G0]
 * Evidence: 48 records of 0xE0 B at .bss+0x97E30 (v0 = (i*8 - i) << 5, t0 =
 * v0 + base); `lw a0,0(t0)` loads the flag word, `ori a0,a0,0x100`,
 * `sw a0,0(t0)` (in the jr delay slot); `sh a1,0x74(a3)` / `sh a2,0x76(v0)`
 * store the two phase values, each through its own copy of the slot address
 * (`daddu a3,t0,zero`, `daddu v0,a3,zero`).
 * Lever: the two 16-bit fields must be declared (and touched) as a two-element
 * array member `short volPhase[2]` at +0x74.  Two separate `short` scalars make
 * gcc factor the shared +0x70 into an `addiu` and store through `4(v0)`/`6(v0)`
 * (10/14 words); the array member keeps the full 0x74/0x76 displacements and
 * reproduces the base copies exactly.
 * UNCONFIRMED: element/field names, prototype (the s70 Sg2Slot layout is
 * reused as-is), whether +0x74 is really a two-element array in the original.
 */
struct Sg2Slot {
    unsigned int flags; int owner; int unk08; int cls; int vab; int ch;
    int unk18; int group;
    char pad20[0x14];
    int masTune;
    char pad38[8];
    int seMasVol; int baseVol; int vol; int masPan; int basePan; int pan;
    int bendRange; int bendValue; int ssa;
    unsigned short adsr1; unsigned short adsr2;
    int unk68; int unk6C; int directPitch;
    short volPhase[2];
    char pad78[8];
    int lfo0; int *lfoTbl; int *lfoCur; int *lfoEnd;
    char pad90[0xC];
    int *lfoVolTbl;
    char padA0[0x40];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotSetVolPhase(int i, short ph1, short ph2) {
    D_kernel_bss_97E30[i].volPhase[0] = ph1;
    D_kernel_bss_97E30[i].volPhase[1] = ph2;
    D_kernel_bss_97E30[i].flags |= 0x100;
}
