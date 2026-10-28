/* KERNEL.XFF @ 0x029E10 (68 B) - Sg2SlotSetLfoPitchTbl   [MATCH: -G0]
 * Evidence: 48 voice slots of 0xE0 B at .bss+0x97E30 (idx*0xE0 = (idx*8-idx)<<5);
 * `a3 = tbl + 0x3C` is computed in the *entry* block (tbl + 15 scaled by 4, i.e.
 * lfoEnd = tbl + 15); the guard is `beqz a2` (tbl == 0).  Three 32-bit stores:
 * 0x84(v1) with v1 = &slot[i]  -> lfoTbl, 0x8(a1) -> lfoCur, 0xC(a1) -> lfoEnd,
 * where a1 = &slot[i] + 0x80 and `v0 = a1` is a second copy of that base.
 * Lever (new): the image keeps TWO bases for the same object, so the C body must
 * mix a pointer local with direct array indexing - `p = &slot[i]; p->lfoTbl =
 * tbl; slot[i].lfoCur = tbl; slot[i].lfoEnd = tbl + 15;` reproduces both the
 * `slot+0x80` base for the cur/end pair and the plain `slot` base (+0x84) for
 * lfoTbl, plus the `daddu v0,a1,zero` copy.  Declaring all three through the
 * index form folds them onto one base (5 words wrong); all three through `p`
 * loses the +0x80 base (48 B).
 * UNCONFIRMED: struct field names beyond the three touched.
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
    short volPhase1; short volPhase2;
    char pad78[8];
    int lfo0; int *lfoTbl; int *lfoCur; int *lfoEnd;
    char pad90[0xC];
    int *lfoVolTbl;
    char padA0[0x40];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
#define slot D_kernel_bss_97E30

void Sg2SlotSetLfoPitchTbl(int i, int *tbl) {
    struct Sg2Slot *p;
    if (tbl != 0) {
        p = &slot[i];
        p->lfoTbl = tbl;
        slot[i].lfoCur = tbl;
        slot[i].lfoEnd = tbl + 15;
    }
}
