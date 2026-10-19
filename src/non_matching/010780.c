/* STATUS (Session 35, 2026-10-19): NON_MATCHING. best score 9 [cc=29].
 * timer compare re-arm over the sorted alarm list (struct N10910 keys f20+f10-f18). Residual =
 * loop tail: original ends the scan with beql exit + b top (t = k in the b slot), ours bnezl back
 * with the next-load stolen. Tried: while/for/goto loop shapes, key inline helper, nothrow SetT2
 * stubs, 991111a/dtls13010.
 * The original .s stays in the build (asm/cod/010780.s); this C
 * draft (Session 35) is kept for the record. */
#include "symbols.h"

struct N10910 {
    struct N10910 *next;            /* 0x00 */
    struct N10910 *prev;            /* 0x04 */
    unsigned int   f08;             /* 0x08 */
    unsigned int   f0C;             /* 0x0C */
    unsigned long long f10;         /* 0x10 */
    unsigned long long f18;         /* 0x18 */
    unsigned long long f20;         /* 0x20 */
};

struct H10910 {
    char pad[0x18];
    struct N10910 *head;            /* 0x18 */
    int f1C;                        /* 0x1C */
};

extern struct H10910 D_00133918;

void SetT2_COMP(int a0);
void SetT2_MODE(int a0);

void func_00110780(unsigned long long now)
{
    struct N10910 *n;
    unsigned long long t, k;
    unsigned int mode;
    int shift;

    n = D_00133918.head;
    if (D_00133918.f1C >= 0)
        return;
    mode = HWREG(EE_T2_MODE);
    if (n == 0) {
        SetT2_COMP(0);
        SetT2_MODE(mode & ~0x800);
        return;
    }
    t = n->f20 + n->f10 - n->f18;
    while ((n = n->next) != 0) {
        k = n->f20 + n->f10 - n->f18;
        if (k >= t + 0x7333)
            break;
        t = k;
    }
    shift = mode & 3;
    if ((long long)(t - now) < 0x7333) {
        SetT2_COMP(HWREG(EE_T2_COUNT) + (0x7333ULL >> (shift * 4)));
        SetT2_MODE(mode & ~0x800);
        return;
    } else {
        SetT2_MODE(mode & ~0x800);
        SetT2_COMP(t >> (shift * 4));
        return;
    }
}
