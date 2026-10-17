/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 6 [cc=29].
 * void tail call (j EIntr) and re-read list head; residual = scheduler puts the p->f00 store first
 * The original .s stays in the build (asm/cod/009C58.s); this C
 * draft (Session 19) is kept for the record. */
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

int DIntr(void);
void EIntr(void);

void sceSifRegisterRpc(int a0, int a1, int a2, int a3, int a4, int a5,
                  struct N09C58 *a6) {
    struct N09C58 *p = (struct N09C58 *)a0;
    struct N09C58 *q;

    DIntr();
    p->f3C = 0;
    p->f38 = 0;
    p->f00 = a1;
    p->f04 = a2;
    p->f08 = a3;
    p->f10 = a4;
    p->f14 = a5;
    p->f40 = a6;
    if (a6->f08 == 0) {
        a6->f08 = (int)p;
    } else {
        q = (struct N09C58 *)a6->f08;
        while (q->f38 != 0)
            q = q->f38;
        q->f38 = p;
    }
    EIntr();
}
/* sceSifRegisterRpc */
