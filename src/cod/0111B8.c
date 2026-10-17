/* asm/cod/0111B8.s -> SetTimerCount.
 * timer SetTimerCount; empty-asm pin keeps the D_00133918 base, elapsed time added before the stores (Session 19)
 * MATCHED. */
struct S111B8 {
    int       f00;   /* 0x00 */
    int       f04;   /* 0x04 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    long long f18;   /* 0x18 */
};

struct T111B8 {
    long long base;  /* 0x00 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    int       f18;   /* 0x18 */
    int       f1C;   /* 0x1C */
};

extern struct T111B8 D_00133918;
int DIntr(void);
int EIntr(void);
long long iGetTimerSystemTime(void);

long long SetTimerCount(int a0, long long a1) {
    struct S111B8 *p;
    int guard;
    long long t;
    long long now;
    long long old;
    struct T111B8 *tp;

    p = (struct S111B8 *)(((unsigned int)a0 >> 10) << 6);
    guard = DIntr();
    if (a0 >= 0 && (a0 & 0x3FF) == p->f08) {
        tp = &D_00133918;
        __asm__ ("" : "+r" (tp));
        if (tp->f1C != a0)
            goto ok;
    }
    if (guard != 0)
        EIntr();
    return -1;
ok:
    t = p->f18;
    if (p->f0C & 1) {
        now = iGetTimerSystemTime();
        old = p->f10;
        p->f18 = a1;
        p->f10 = now;
        t = t + (now - old);
    } else {
        p->f18 = a1;
    }
    if (guard != 0)
        EIntr();
    return t;
}
