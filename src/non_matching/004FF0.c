/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 8 [cc=296].
 * R2 w45a_1: block-layout (5-nop hang blocks not reproducible from C)
 * The original .s stays in the build (asm/cod/004FF0.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_0013A118;                 /* .sbss scalar (%gp_rel) */
extern void (*D_0013A11C)(void);        /* .sbss scalar (%gp_rel) */
extern char D_0013A120[];               /* lui/%lo */
extern char D_0013A128[];               /* lui/%lo */
extern char D_001373F0[];               /* lui/%lo */

int  WaitSema(int a0);
int  iSignalSema(int a0);
void PutStringS(int a0, int a1, ...);
int  sceDevctl(int a0, int a1, int a2, int a3, int a4);
int  sceCdPowerOff(int *p);

void func_00104FF0(void) {
    int x;
    int r;

    for (;;) {
        WaitSema(D_0013A118);
        if (D_0013A11C != 0)
            D_0013A11C();
        PutStringS(0x4080FF80, (int)D_001373F0);
        sceDevctl((int)D_0013A120, 0x5003, 0, 0, 0);
        while (sceDevctl((int)D_0013A128, 0x4402, 0, 0, 0) < 0)
            ;
        do {
            r = sceCdPowerOff(&x);
        } while (r == 0 || x != 0);
    }
}

void func_001050A0(void) {
    iSignalSema(D_0013A118);
}
