/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 13 [cc=29].
 * R2 w45a_3: sw $gp,0x2C($s0) has no C spelling
 * The original .s stays in the build (asm/cod/0113E0.s); this C
 * draft (Session 8) is kept for the record. */
struct S113E0 {
    int       f00;   /* 0x00 */
    int       f04;   /* 0x04 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    long long f18;   /* 0x18 */
    long long f20;   /* 0x20 */
    int       f28;   /* 0x28 */
    int       f2C;   /* 0x2C */
    int       f30;   /* 0x30 */
};

struct T113E0 {
    long long base;  /* 0x00 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    int       f18;   /* 0x18 */
    int       f1C;   /* 0x1C */
};

extern struct T113E0 D_00133918;
int func_00110998(void *a0);
int func_00110910(void *a0);
long long iGetTimerSystemTime(void);
int func_00110780(long long a0);

int iSetTimerHandler(int a0, long long a1, int a2, int a3) {
    struct S113E0 *p;
    int m;

    p = (struct S113E0 *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != p->f08)
        return 0x80008002;
    if (D_00133918.f1C == a0)
        return 0x80000010;
    m = p->f0C;
    if (m & 2) {
        func_00110998(p);
        m = p->f0C;
    }
    p->f28 = a2;
    if (a2 == 0) {
        p->f0C = m & 0xFFFFFFFD;
    } else {
        p->f0C = m | 2;
        p->f20 = a1;
        p->f2C = 0;   /* UNCONFIRMED: the original stores $gp here */
        p->f30 = a3;
        if (p->f0C & 1)
            func_00110910(p);
    }
    func_00110780(iGetTimerSystemTime());
    return 0;
}
