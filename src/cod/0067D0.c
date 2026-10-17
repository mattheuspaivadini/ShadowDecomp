/* asm/cod/0067D0.s -> SetDrawEnvironment.
 * boot GS draw env (game code); p[2] before p[3] store order (Session 19)
 * MATCHED. */
extern int  D_001321A0[];   /* lui/%lo, address ORed with 0x20000000 */

int  sceGsSetDefAlphaEnv(long long *p, short a1);
int  sceGsSyncPath(int mode, int timeout);
int  sceGsPutDrawEnv(void *env);

void SetDrawEnvironment(int a0) {
    long long *p;

    p = (long long *)((unsigned int)D_001321A0 | 0x20000000);
    sceGsSetDefAlphaEnv(p + 4, 0);
    switch (a0) {
    case 0:
        p[4] = 0x48;
        break;
    case 1:
        p[4] = 0x44;
        break;
    case 2:
        p[4] = 0x42;
        break;
    case 3:
        p[4] = 0x2800000064LL;
        break;
    case 4:
        p[4] = 0x68;
        break;
    }
    p[2] = 0x20000;
    p[3] = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
