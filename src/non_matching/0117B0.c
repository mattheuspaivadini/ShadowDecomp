/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 18 [cc=29].
 * R2 w45a_3: free-list pop/push-back
 * The original .s stays in the build (asm/cod/0117B0.s); this C
 * draft (Session 8) is kept for the record. */
struct S011750 {
    struct S011750 *next;      /* 0x00 */
    int             field04;   /* 0x04 */
    int           (*fn)();     /* 0x08 */
    int             field0C;   /* 0x0C */
};

extern struct S011750 *D_0014AC80[];   /* lui/%lo -> non-small */
int DIntr(void);
int EIntr(void);
int AllocTimerCounter(void);
int SetTimerHandler(int a0, int a1, int (*a2)(), void *a3);
int StartTimerCounter(int a0);
int func_00111750(int a0, int a1, int a2, void *a3);

int SetTimerAlarm(int a0, int (*a1)(), int a2) {
    struct S011750 *n;
    struct S011750 *old;
    int guard;
    int r;

    if (a1 == 0)
        return 0x80000016;
    guard = DIntr();
    n = D_0014AC80[0];
    if (n != 0)
        D_0014AC80[0] = n->next;
    if (n == 0) {
        if (guard != 0)
            EIntr();
        return 0x80008005;
    }
    r = AllocTimerCounter();
    if (r < 0) {
        old = D_0014AC80[0];
        D_0014AC80[0] = n;
        n->next = old;
        n->field04 = 0;
        if (guard != 0)
            EIntr();
        return r;
    }
    n->fn = a1;
    n->field0C = a2;
    n->field04 = r;
    SetTimerHandler(r, a0, func_00111750, n);
    StartTimerCounter(r);
    if (guard != 0)
        EIntr();
    return ((int)n << 4) | (r & 0xFE) | 1;
}
