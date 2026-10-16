/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 13 [cc=29].
 * R1 wave3e: unsigned-shift cast hoisted above the bltz guard
 * The original .s stays in the build (asm/cod/011A78.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0014AC80[];   /* .bss 0x0014AC80: free-list head */

int iFreeTimerCounter(int a0);

int iReleaseTimerAlarm(int a0) {
    int *p;
    int  r;
    int  old;

    p = (int *)(((unsigned int)a0 >> 8) << 4);
    if (a0 < 0)
        return 0x80008002;
    if ((a0 ^ p[1]) & 0xFF)
        return 0x80008002;
    r = iFreeTimerCounter(p[1]);
    if (r != 0)
        return r;
    old = D_0014AC80[0];
    D_0014AC80[0] = (int)p;
    p[0] = old;
    p[1] = 0;
    return r;
}
