/* asm/cod/0147C0.s -> func_001147C0.
 * DMA channel wait with timeout; volatile CHCR + pre-decremented 0x1000000 counter (Session 22)
 * MATCHED. */
int scePrintf(const char *msg);
int sceDmaPause(volatile int *p);

extern char D_001384F0[];   /* lui/%lo: non-small */

void func_001147C0(volatile int *p) {
    int i = 0x1000000;
    while (*p & 0x100) {
        if (--i < 0) {
            scePrintf(D_001384F0);
            sceDmaPause(p);
        }
    }
}
