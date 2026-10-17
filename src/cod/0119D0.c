/* asm/cod/0119D0.s -> ReleaseTimerAlarm.
 * timer ReleaseTimerAlarm; DIntr-guarded twin of iReleaseTimerAlarm (Session 19)
 * MATCHED. */
struct alarm {
    struct alarm *next;     /* 0x00 */
    volatile int id;        /* 0x04 */
    int f08;
    int f0C;
};

extern struct alarm *D_0014AC80 __attribute__((section(".data")));

int DIntr(void);
int EIntr(void);
int FreeTimerCounter(int a0);

int ReleaseTimerAlarm(int a0) {
    struct alarm *p = (struct alarm *)(((unsigned int)a0 >> 8) << 4);
    struct alarm *old;
    int g;

    g = DIntr();
    if (a0 < 0 || ((a0 ^ p->id) & 0xFF) != 0) {
        if (g != 0)
            EIntr();
        return 0x80008002;
    }
    FreeTimerCounter(p->id);
    old = D_0014AC80;
    D_0014AC80 = p;
    p->next = old;
    p->id = 0;
    if (g != 0)
        EIntr();
    return 0;
}
