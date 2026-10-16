/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/0111B8.s); this C
 * draft (10) is kept for the record. */
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
int func_0010FB20(void);
int func_0010FB70(void);
long long func_00110C78(void);

long long SetTimerCount(int a0, long long a1) {
    struct S111B8 *p;
    int guard;
    long long t;
    long long now;
    long long old;

    p = (struct S111B8 *)(((unsigned int)a0 >> 10) << 6);
    guard = func_0010FB20();
    if (a0 < 0 || (a0 & 0x3FF) != p->f08 || D_00133918.f1C == a0) {
        if (guard != 0)
            func_0010FB70();
        return -1;
    }
    t = p->f18;
    if (p->f0C & 1) {
        now = func_00110C78();
        old = p->f10;
        p->f18 = a1;
        t = t + (now - old);
        p->f10 = now;
    } else {
        p->f18 = a1;
    }
    if (guard != 0)
        func_0010FB70();
    return t;
}
