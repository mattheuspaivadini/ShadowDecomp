/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 44 [cc=29].
 * R2 w45a_3: reg-alloc (lbu/lb dual read)
 * The original .s stays in the build (asm/cod/00F168.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_001381A0[];   /* lui/addiu -> non-small */
extern char D_001381B0[];   /* lui/addiu -> non-small */
int scePrintf(void *a0, void *a1);
int sceSifInitRpc(int a0);
int sceSifExitRpc(void);
int sceSifResetIop(void *a0, int a1);

int sceSifRebootIop(char *a0) {
    char buf[0x50];
    char *p;
    char *d;
    char *s;
    unsigned char c;
    unsigned char first;
    int n;

    p = a0;
    if (*p != 0) {
        while (*++p != 0)
            ;
    }
    n = (int)(p - a0) + 0xB;
    if (n >= 0x51) {
        scePrintf(D_001381B0, a0);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = buf;
    first = *(unsigned char *)a0;
    s = D_001381A0;
    c = *(unsigned char *)s;
    while (*s != 0) {
        *d++ = c;
        s++;
        c = *(unsigned char *)s;
    }
    c = first;
    while (c != 0) {
        *d++ = c;
        a0++;
        c = *a0;
    }
    *d = 0;
    sceSifResetIop(buf, 0);
    return 0;
}
