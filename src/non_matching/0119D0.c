/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 16 [cc=29].
 * R4 w25a_1: guarded 16-byte node free
 * The original .s stays in the build (asm/cod/0119D0.s); this C
 * draft (Session 8) is kept for the record. */
struct N119D0 {
    struct N119D0 *next;    /* 0x00 */
    int id;                 /* 0x04 */
};

extern struct N119D0 *D_0014AC80[];

int DIntr(void);
int EIntr(void);
int FreeTimerCounter(int a0);

unsigned int ReleaseTimerAlarm(int a0) {
    int g;
    struct N119D0 *p;
    struct N119D0 *old;

    g = DIntr();
    p = (struct N119D0 *)(((unsigned int)a0 >> 8) << 4);
    if (a0 < 0 || ((a0 ^ p->id) & 0xFF) != 0) {
        if (g != 0)
            EIntr();
        return 0x80008002u;
    }
    FreeTimerCounter(p->id);
    old = D_0014AC80[0];
    D_0014AC80[0] = p;
    p->next = old;
    p->id = 0;
    if (g != 0)
        EIntr();
    return 0;
}
