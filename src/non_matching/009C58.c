/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 11 [cc=29].
 * R2 w45a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/009C58.s); this C
 * draft (Session 8) is kept for the record. */
struct N09C58 {
    int             f00;    /* 0x00 */
    int             f04;    /* 0x04 */
    int             f08;    /* 0x08 */
    int             f0C;    /* 0x0C */
    int             f10;    /* 0x10 */
    int             f14;    /* 0x14 */
    char            pad18[0x20];
    struct N09C58  *f38;    /* 0x38 */
    int             f3C;    /* 0x3C */
    struct N09C58  *f40;    /* 0x40 */
};

int func_0010FB20(void);
int func_0010FB70(void);

int func_00109C58(int a0, int a1, int a2, int a3, int a4, int a5,
                  struct N09C58 *a6) {
    struct N09C58 *p = (struct N09C58 *)a0;
    struct N09C58 *q;

    func_0010FB20();
    p->f3C = 0;
    p->f38 = 0;
    p->f00 = a1;
    q = a6->f08;
    p->f04 = a2;
    p->f08 = a3;
    p->f10 = a4;
    p->f14 = a5;
    p->f40 = a6;
    if (q == 0) {
        a6->f08 = (int)p;
    } else {
        while (q->f38 != 0)
            q = q->f38;
        q->f38 = p;
    }
    return func_0010FB70();
}
