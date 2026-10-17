/* asm/cod/0118E0.s -> iSetTimerAlarm.
 * timer iSetTimerAlarm; pop re-tested (asm pin), volatile id (Session 19)
 * MATCHED. */
struct S0118E0 {
    struct S0118E0 *next;      /* 0x00 */
    volatile int    field04;   /* 0x04 */
    int           (*fn)();     /* 0x08 */
    int             field0C;   /* 0x0C */
};

extern struct S0118E0 *D_0014AC80[];   /* lui/%lo -> non-small */
int iAllocTimerCounter(void);
int iSetTimerHandler(int a0, long long a1, int (*a2)(), void *a3);
int iStartTimerCounter(int a0);
int func_00111750(int a0, int a1, int a2, void *a3);

int iSetTimerAlarm(int a0, int (*a1)(), int a2) {
    struct S0118E0 *n;
    struct S0118E0 *old;
    int r;

    if (a1 == 0)
        return 0x80000016;
    n = D_0014AC80[0];
    if (n != 0)
        D_0014AC80[0] = n->next;
    /* UNCONFIRMED: the image re-tests n after the pop (no jump threading);
     * the empty asm pin reproduces that, the original spelling is unknown. */
    __asm__ ("" : "+r" (n));
    if (n == 0)
        return 0x80008005;
    r = iAllocTimerCounter();
    if (r < 0) {
        old = D_0014AC80[0];
        D_0014AC80[0] = n;
        n->next = old;
        n->field04 = 0;
        return r;
    }
    n->fn = a1;
    n->field0C = a2;
    n->field04 = r;
    iSetTimerHandler(r, (long long)a0, func_00111750, n);
    iStartTimerCounter(r);
    return ((int)n << 4) | (r & 0xFE) | 1;
}
