/* KERNEL.XFF @ 0x02A5E8 (268 B) - Sg2SlotVabKeyOff   [MATCH: -G0 -fno-strict-aliasing]
 * Evidence: intr = DIntr() (first argument registers a0/a1/a2 are saved to
 * s2/s1/s0 because of the call); scan the 48 voice slots at .bss+0x97E30
 * (0xE0-byte records) for flags&1 && +0x10 == arg0 (vab) && +0x14 == arg1 (ch)
 * && +0x24 == arg2; on a hit clear bit 3 of flags (`andi a1,0xfffffff7`) and set
 * one bit of the two-word mask at .bss+0x97DF8 - word 0 for i < 24 (bit i),
 * word 1 for i >= 24 (bit i-24, `addiu v0,i,-0x18`); then `if (intr) EIntr();`
 * emitted as the shipped tail `j EIntr` with the frame torn down first.
 * The word select is `slti v0,i,0x18; move v1,4; movn v1,zero,v0; addu v1,t6`
 * and the bit is computed in the delay slot of the branch that skips it.
 * LEVER: the mask update must be ONE statement whose word index is a ternary
 * and whose value is a *parenthesised* ternary of shifts:
 *     D_kernel_bss_97DF8[i < 24 ? 0 : 1] |= (i < 24) ? (1 << i) : (1 << (i - 24));
 * Written as `1 << (i < 24 ? i : i - 24)` the object is identical except that
 * gcc mirrors the two shift arms (bnez + the i-24 arm in fall-through, 24
 * words); the extra parentheses around each `1 << ...` flip the arm layout to
 * the shipped `beqz` + `1 << i` fall-through.  A plain if/else costs a separate
 * load+store per word (39 words); a pointer/`j` temporary regresses too.
 * UNCONFIRMED: slot field names (+0x24's meaning), EIntr's prototype.
 */
int DIntr(void);
void EIntr(void);

struct Sg2Slot {
    unsigned int flags;         /* 0x00 */
    int owner;                  /* 0x04 */
    int unk08;                  /* 0x08 */
    int cls;                    /* 0x0C */
    int vab;                    /* 0x10 */
    int ch;                     /* 0x14 */
    int unk18;                  /* 0x18 */
    int group;                  /* 0x1C */
    int unk20;                  /* 0x20 */
    int unk24;                  /* 0x24 */
    int unk28;                  /* 0x28 */
    int unk2C;                  /* 0x2C */
    int unk30;                  /* 0x30 */
    int masTune;                /* 0x34 */
    int unk38;                  /* 0x38 */
    int unk3C;                  /* 0x3C */
    int seMasVol;               /* 0x40 */
    int baseVol;                /* 0x44 */
    int vol;                    /* 0x48 */
    int masPan;                 /* 0x4C */
    int basePan;                /* 0x50 */
    int pan;                    /* 0x54 */
    int bendRange;              /* 0x58 */
    int bendValue;              /* 0x5C */
    int ssa;                    /* 0x60 */
    unsigned short adsr1;       /* 0x64 */
    unsigned short adsr2;       /* 0x66 */
    int unk68;                  /* 0x68 */
    int unk6C;                  /* 0x6C */
    int directPitch;            /* 0x70 */
    short volPhase1;            /* 0x74 */
    short volPhase2;            /* 0x76 */
    int unk78;                  /* 0x78 */
    int unk7C;                  /* 0x7C */
    int lfoPitchSpeed;          /* 0x80 */
    int *lfoPitchTbl;           /* 0x84 */
    int *lfoPitchCur;           /* 0x88 */
    int *lfoPitchEnd;           /* 0x8C */
    char pad90[0x50];           /* 0x90..0xDF */
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
extern unsigned int D_kernel_bss_97DF8[2];

void Sg2SlotVabKeyOff(int vab, int ch, int unk24) {
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if (!(D_kernel_bss_97E30[i].flags & 1))
            continue;
        if (D_kernel_bss_97E30[i].vab != vab)
            continue;
        if (D_kernel_bss_97E30[i].ch != ch)
            continue;
        if (D_kernel_bss_97E30[i].unk24 != unk24)
            continue;
        D_kernel_bss_97E30[i].flags &= ~8;
        D_kernel_bss_97DF8[i < 24 ? 0 : 1] |= (i < 24) ? (1 << i) : (1 << (i - 24));
    }
    if (intr)
        EIntr();
}
