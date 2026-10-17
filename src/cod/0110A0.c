/* asm/cod/0110A0.s -> iStopTimerCounter.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
struct S110A0 {
    int       f00;   /* 0x00 */
    int       f04;   /* 0x04 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    long long f18;   /* 0x18 */
};

struct T110A0 {
    long long base;  /* 0x00 */
    int       f08;   /* 0x08 */
    int       f0C;   /* 0x0C */
    long long f10;   /* 0x10 */
    int       f18;   /* 0x18 */
    int       f1C;   /* 0x1C */
};

extern struct T110A0 D_00133918;
long long iGetTimerSystemTime(void);
int func_00110998(void *a0);
int func_00110780(long long a0);

int iStopTimerCounter(int a0) {
    struct S110A0 *p;
    long long now;
    long long old;
    int m;
    struct T110A0 *h;

    p = (struct S110A0 *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != p->f08)
        return 0x80008002;
    h = &D_00133918;
    asm volatile ("" : "+r" (h));
    if (h->f1C == a0)
        return 0x80000010;
    if ((p->f0C & 1) == 0)
        return 0;
    now = iGetTimerSystemTime();
    m = p->f0C;
    old = p->f10;
    p->f18 = p->f18 + (now - old);
    p->f0C = m & 0xFFFFFFFE;
    if (m & 2) {
        func_00110998(p);
        func_00110780(now);
    }
    return 1;
}
