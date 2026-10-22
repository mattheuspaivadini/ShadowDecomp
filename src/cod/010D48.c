/* asm/cod/010D48.s -> iAllocTimerCounter.
 * timer TU iAllocTimerCounter; volatile D.f0C, operand-only asm fence on the f10 increment (Session 42)
 * MATCHED. */
struct N10D48 {
    struct N10D48 *next;    /* 0x00 */
    int            f04;     /* 0x04 */
    int            f08;     /* 0x08 */
    int            f0C;     /* 0x0C */
    int            f10;     /* 0x10 */
    int            f14;     /* 0x14 */
    long long      f18;     /* 0x18 */
    int            f20;     /* 0x20 */
    int            f24;     /* 0x24 */
    int            f28;     /* 0x28 */
};

struct D10D48 {
    int             pad00;  /* 0x00 */
    int             pad04;  /* 0x04 */
    int             pad08;  /* 0x08 */
    volatile int    f0C;    /* 0x0C */
    int             f10;    /* 0x10 */
    struct N10D48  *f14;    /* 0x14 */
};

extern struct D10D48 D_00133918;

int iAllocTimerCounter(void) {
    volatile struct N10D48 *n;
    struct N10D48 *nx;
    unsigned int v;
    unsigned int t10;
    int t0c;

    n = D_00133918.f14;
    if (n == 0)
        return 0x80008005;
    v = (unsigned int)n << 4;
    t10 = D_00133918.f10;
    t10 = t10 + 1;
    nx = n->next;
    asm volatile("" : : "r"(t10));    /* keeps the D.f10 increment above the n->f28 store */
    n->f28 = 0;
    D_00133918.f10 = t10;
    n->f0C = 0;
    D_00133918.f14 = nx;
    t0c = D_00133918.f0C;
    n->f18 = 0;
    D_00133918.f0C = t0c + 1;
    n->f08 = ((D_00133918.f0C << 1) & 0x3FE) | 1;
    return (int)(v | n->f08);
}
