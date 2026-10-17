/* asm/cod/004FF0.s -> func_00104FF0.
 * power-off thread loop (boot game code); sceDevctl takes 6 args (Session 19)
 * MATCHED. */
extern int  D_0013A118;                 /* .sbss scalar (%gp_rel) */
extern void (*D_0013A11C)(void);        /* .sbss scalar (%gp_rel) */
extern char D_0013A120[];               /* lui/%lo */
extern char D_0013A128[];               /* lui/%lo */
extern char D_001373F0[];               /* lui/%lo */

int  WaitSema(int a0);
int  iSignalSema(int a0);
void PutStringS(int a0, int a1, ...);
int  sceDevctl(const char *name, int cmd, void *arg, int arglen, void *buf, int buflen);
int  sceCdPowerOff(int *p);

void func_00104FF0(void) {
    int x;
    int r;

    for (;;) {
        WaitSema(D_0013A118);
        if (D_0013A11C != 0)
            D_0013A11C();
        PutStringS(0x4080FF80, (int)D_001373F0);
        sceDevctl(D_0013A120, 0x5003, 0, 0, 0, 0);
        while (sceDevctl(D_0013A128, 0x4402, 0, 0, 0, 0) < 0)
            ;
        do {
            r = sceCdPowerOff(&x);
        } while (r == 0 || x != 0);
    }
}

void func_001050A0(void) {
    iSignalSema(D_0013A118);
}
