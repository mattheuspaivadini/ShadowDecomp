/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 28 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/022EA8.s); this C
 * draft (Session 9) is kept for the record. */
struct S22EA8 {
    int f00;    /* 0x00 */
    int f04;    /* 0x04 */
    int f08;    /* 0x08 */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
};

extern int D_00169F04[];    /* one pointer-sized slot each (lui/%lo) */
extern int D_00169F08[];
extern int D_00169F0C[];

struct S22EA8 *func_00122EA8(int cmd, struct S22EA8 *p) {
    int r;

    r = -1;
    switch (cmd) {
    case 0xC: {
        int fp;

        fp = D_00169F04[0];
        if (fp != 0)
            r = ((int (*)(int, int, int, int, int))fp)(
                (int)p + 0x10, (int)p + p->f08 + 0x10, p->f00, p->f04,
                (int)p + 4);
        break;
    }
    case 0xD: {
        int fp;

        fp = D_00169F08[0];
        if (fp != 0)
            r = ((int (*)(int, int, int, int, int, int))fp)(
                p->f00, (int)p + 0x14, (int)p + p->f04 + 0x14, (int)p + 4,
                p->f0C, p->f10);
        break;
    }
    case 0xE: {
        int fp;

        fp = D_00169F0C[0];
        if (fp != 0)
            r = ((int (*)(int))fp)(p->f00);
        break;
    }
    }
    p->f00 = r;
    return p;
}
