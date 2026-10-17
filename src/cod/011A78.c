/* asm/cod/011A78.s -> iReleaseTimerAlarm.
 * timer iReleaseTimerAlarm; volatile id, push only when the counter freed (Session 19)
 * MATCHED. */
struct alarm {
    struct alarm *next;     /* 0x00 */
    volatile int id;        /* 0x04 */
    int f08;
    int f0C;
};

extern struct alarm *D_0014AC80 __attribute__((section(".data")));   /* .bss 0x0014AC80: free-list head */

int iFreeTimerCounter(int a0);

int iReleaseTimerAlarm(int a0) {
    struct alarm *p = (struct alarm *)(((unsigned int)a0 >> 8) << 4);
    int r;

    if (a0 < 0 || ((a0 ^ p->id) & 0xFF) != 0)
        return 0x80008002;
    r = iFreeTimerCounter(p->id);
    if (r == 0) {
        struct alarm *old = D_0014AC80;
        D_0014AC80 = p;
        p->next = old;
        p->id = 0;
    }
    return r;
}
