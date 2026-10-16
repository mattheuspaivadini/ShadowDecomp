/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/006588.s); this C
 * draft (10) is kept for the record. */
extern int  D_0013A130;     /* .sdata/.sbss scalar (%gp_rel) */
extern int  D_00131FD0[];   /* lui/%lo, address ORed with 0x20000000 */

int  func_00113F10(long long *a0, int a1, short a2, short a3, int a4, int a5,
                   int a6, int a7, int a8, int a9, int a10, int a11);
int  func_00114020(long long *p, short a1);
int  sceGsSyncPath(int mode, int timeout);
int  sceGsPutDrawEnv(void *env);

void SetTextureWithFrameBuffer(int a0) {
    long long *p;
    long long *q;
    int n;

    n = D_0013A130;
    p = (long long *)((unsigned int)D_00131FD0 | 0x20000000);
    q = p + 4;
    func_00113F10(p + 0xC, 0, (short)a0, (short)(n / 64), 1, 0xA, 8, 0,
                  0, 0, 0, 1);
    func_00114020(q, 0);
    q[0] = 0x44;
    p[3] = 0x47;
    p[14] = 0x61;
    p[2] = 0x20000;
    p[18] = 0;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
