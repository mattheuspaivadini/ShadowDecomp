/* STATUS (Session 41, 2026-10-21): NON_MATCHING. best score 36 (was 44; sw.py diff lines).
 * Length test written as (unsigned int)(p + 11 - arg) > 0x50 gives the image's p - (arg - 11) on both paths. Residual: register roles of the copy loops (image d = v1, hoisted *arg in a1 copied to a0); 48 declaration/type/placement variants and inline helpers did not move it.
 * ps2sdk SifIopReboot shape: inline strlen loop, "rom0:UDNL " prefix pointer kept in s1 from the start, strcat loop, return the reset result. Residual = the strlen block (original computes p - (arg - 11) on both paths with the scan pointer in a0) and the register roles of the copy loops.
 * The original .s stays in the build (asm/cod/00F168.s); this C
 * draft (Session 23) is kept for the record. */
extern char D_001381A0[];   /* "rom0:UDNL " */
extern char D_001381B0[];   /* "too long parameter ..." */
int scePrintf(const char *fmt, ...);
int sceSifInitRpc(int mode);
int sceSifExitRpc(void);
int sceSifResetIop(const char *arg, int mode);

int sceSifRebootIop(const char *arg) {
    char buf[0x50];
    const char *s = D_001381A0;
    const char *p;
    char *d;
    char c;

    p = arg;
    if (*p)
        while (*++p)
            ;
    if ((unsigned int)(p + 11 - arg) > 0x50) {
        scePrintf(D_001381B0, arg);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = buf;
    while (*s)
        *d++ = *s++;
    while (*arg)
        *d++ = *arg++;
    *d = 0;
    return sceSifResetIop(buf, 0);
}
