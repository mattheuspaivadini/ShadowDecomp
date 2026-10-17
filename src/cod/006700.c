/* asm/cod/006700.s -> SetDrawnTextureEnvironment.
 * boot GS drawn-tex env; p[18] and p[10] cleared (Session 19)
 * MATCHED. */
extern int  SCREEN_WIDTH;     /* .sdata/.sbss scalar (%gp_rel) */
extern int  D_00132100[];   /* lui/%lo, address ORed with 0x20000000 */

int  sceGsSetDefTexEnv(long long *a0, int a1, short a2, short a3, int a4, int a5,
                   int a6, int a7, int a8, int a9, int a10, int a11);
int  sceGsSetDefAlphaEnv(long long *p, short a1);
int  sceGsSyncPath(int mode, int timeout);
int  sceGsPutDrawEnv(void *env);

void SetDrawnTextureEnvironment(int a0) {
    long long *p;
    long long *q;
    int n;

    n = SCREEN_WIDTH;
    p = (long long *)((unsigned int)D_00132100 | 0x20000000);
    q = p + 4;
    sceGsSetDefTexEnv(p + 0xC, 0, (short)a0, (short)(n / 64), 0, 0xA, 8, 0,
                  0, 0, 0, 1);
    sceGsSetDefAlphaEnv(q, 0);
    q[0] = 0x44;
    p[2] = 0x20000;
    p[3] = 0x47;
    p[14] = 0x61;
    p[18] = 0;
    p[10] = 0;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
