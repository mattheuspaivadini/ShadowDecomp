/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 2 [cc=296 -g0 -fno-delayed-branch -G0].
 * struct-array + pointer pair; residual = sw/addiu(i--) schedule in the short loop (2.9 cc1 schedules sw first but pads the loop with 3 nops; 2.96 pads 1 nop like the image but hoists i--)
 * The original .s stays in the build (asm/cod/011700.s); this C
 * draft (Session 19) is kept for the record. */
struct alarm {
    struct alarm *next;
    int f04;
    int f08;
    int f0C;
};

extern struct alarm D_0014A880[64];
extern struct alarm *D_0014AC80;

int _InitAlarm(void) {
    struct alarm *p, *q;
    int i;

    D_0014AC80 = D_0014A880;
    p = &D_0014A880[63];
    q = &D_0014A880[64];
    for (i = 63; i >= 0; i--) {
        p->next = q;
        p--;
        q--;
    }
    D_0014A880[63].next = 0;
    return 0;
}
