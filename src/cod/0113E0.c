/* asm/cod/0113E0.s -> iSetTimerHandler.
 * timer iSetTimerHandler; $gp saved with asm volatile (memory clobber forces the flag reload), base pin (Session 19)
 * MATCHED. */
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
    struct T113E0 *t;
    int m;

    p = (struct S113E0 *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != p->f08)
        return 0x80008002;
    t = &D_00133918;
    __asm__ ("" : "+r" (t));
    if (t->f1C == a0)
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
        p->f20 = a1;
        p->f0C = m | 2;
        __asm__ volatile ("sw $gp, 0x2c(%0)" : : "r" (p) : "memory");
        p->f30 = a3;
        if (p->f0C & 1)
            func_00110910(p);
    }
    func_00110780(iGetTimerSystemTime());
    return 0;
}
