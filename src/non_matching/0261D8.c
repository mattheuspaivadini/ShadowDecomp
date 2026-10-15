/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 6 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0261D8.s); this C
 * draft (Session 9) is kept for the record. */
struct N0261D8 {
    int f00;                  /* 0x00 */
    int f04;                  /* 0x04 */
    int f08;                  /* 0x08 key */
    int f0C;                  /* 0x0C */
    int f10;                  /* 0x10 */
    struct N0261D8 *f14;      /* 0x14 next */
};

extern int D_00169F90[];    /* list head (absolute: lui/%lo + lw) */
extern __attribute__((section(".data"))) int D_001329A4;   /* pool semaphore */

int func_00107020(int sema);
int func_00107000(int sema);
int func_001277C0(int node);
int func_00127448(void);

int func_001261D8(int key) {
    struct N0261D8 *n;
    struct N0261D8 **pp;

    func_00107020(D_001329A4);
    pp = (struct N0261D8 **)&D_00169F90[0];
    n = *pp;
    if (n != 0) {
        do {
            if (n->f08 == key) {
                *pp = n->f14;
                if (n->f0C != 0 && n->f0C != key)
                    func_001277C0(n->f0C);
                func_00107000(D_001329A4);
                return n;
            }
            pp = &n->f14;
            n = *pp;
        } while (n != 0);
    }
    func_00107000(D_001329A4);
    return func_00127448();
}
