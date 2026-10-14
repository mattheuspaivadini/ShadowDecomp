/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 22 [cc=29, default].
 * Timer 2 readout; -g0/-g2 and both revisions differ.
 * The original .s stays in the build (asm/cod/010C78.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/010C78.s -> func_00110C78 @ 0x00110C78 (0x4C bytes, 19 insns)
 *
 * EE Timer 2 readout. The two hardware registers are reached through ONE base
 * register (`lwu 0x0(v1)` + `lw 0x10(v1)`, v1 = 0x10001000), so the address is
 * held in a single `volatile unsigned int *` local (count = t2[0],
 * mode = t2[4]) rather than as two standalone HWREG constants (compare the
 * matched 010640.c, whose HWREG form materialises 0x10001010 on its own).
 *
 *   count = T2_COUNT; mode = T2_MODE; base = D_00133918;
 *   if (mode & 0x800) { count = T2_COUNT; base = base + 1; }   (overflow carry)
 *   src = mode & 3;                                  (clock source)
 *   value = count | (base << 16);
 *   scale = 2; if (src == 0) scale = 0;              (the `movz` shape)
 *   return value << (scale << src);                  (two `dsllv`)
 *
 * The `dsllv` pair means the scale is 64-bit (`unsigned long long`), and `lwu`
 * means the count is read zero-extended into the 64-bit expression. Hardware
 * register identities from docs/structs.md ("Hardware registers"); D_00133918
 * is the 64-bit software time base (see the matched 010910.c, whose 0x18 field
 * lives in the same object).
 * MATCH GUESS: cc=29 (if-converted `movz` + dsllv)
 */
struct T133918 {
    unsigned long long base;        /* 0x00 time base */
    char pad[0x18];
};

extern struct T133918 D_00133918;

unsigned long long func_00110C78(void) {
    volatile unsigned int *t2;
    unsigned int count;
    unsigned int mode;
    unsigned int src;
    unsigned long long value;
    unsigned long long scale;

    t2 = (volatile unsigned int *)0x10001000;
    count = t2[0];
    mode = t2[4];
    value = D_00133918.base;
    if (mode & 0x800) {
        count = t2[0];
        value = value + 1;
    }
    src = mode & 3;
    value = count | (value << 16);
    scale = 2;
    if (src == 0)
        scale = 0;
    return value << (scale << src);
}
