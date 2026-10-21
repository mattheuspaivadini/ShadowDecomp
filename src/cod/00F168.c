/* asm/cod/00F168.s -> sceSifRebootIop.
 * sceSifRebootIop; inline strlen/strcat loops, asm use of arg after sceSifExitRpc (Session 42)
 * MATCHED. */
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
    asm volatile("" : : "r"(arg));    /* arg used here: the *arg load is hoisted above the prefix loop */
    d = buf;
    while (*s)
        *d++ = *s++;
    while (*arg)
        *d++ = *arg++;
    *d = 0;
    return sceSifResetIop(buf, 0);
}
