/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 32 [cc=296].
 * R2 w45a_0: reg-alloc (clear loop entered at tab + n*0x1C + 4)
 * The original .s stays in the build (asm/cod/001950.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00131CB8[];

struct Rec00101950 {
    int  f0;        /* 0x00 */
    int  f4;        /* 0x04 */
    char pad08[0x4];
    int  fC;        /* 0x0C */
    char pad10[0x10];
};

struct Mod00101950 {
    int  f0;        /* 0x00 */
    char pad[0x34];
    int  f38;       /* 0x38 */
    struct Rec00101950 *f3C;    /* 0x3C */
};

void DisposeRelocationElement(struct Mod00101950 *m, void (*cb)(struct Mod00101950 *, int)) {
    struct Rec00101950 *tab;
    int n;
    int sum;
    int i;

    if (m->f0 != D_00131CB8[0])
        return;
    n = m->f38 >> 1;
    tab = m->f3C;
    sum = 0;
    if (n > 0) {
        for (i = 0; i < n; i++)
            sum += tab[i].f4;
    }
    cb(m, tab[0].fC + (sum << 3));
    if (n > 0) {
        for (i = 0; i < n; i++)
            tab[n + i].f4 = 0;
    }
}
