/* asm/cod/014830.s -> func_00114830.
 * DMA wait-until-address with optional timeout; volatile unsigned MADR compare + pre-decrement (Session 22)
 * MATCHED. */
extern char D_001384F0[];

int  scePrintf(const char *msg);
void sceDmaPause(volatile int *p);

void func_00114830(volatile unsigned int *p, unsigned int a1, int a2) {
    int i = 0x1000000;
    if (a2)
        i = a2;
    while (p[4] < a1) {
        if (--i < 0) {
            scePrintf(D_001384F0);
            sceDmaPause((volatile int *)p);
        }
    }
}
