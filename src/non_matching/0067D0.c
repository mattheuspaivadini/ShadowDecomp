/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/0067D0.s); this C
 * draft (10) is kept for the record. */
extern int  D_001321A0[];   /* lui/%lo, address ORed with 0x20000000 */

int  func_00114020(long long *p, short a1);
int  sceGsSyncPath(int mode, int timeout);
int  sceGsPutDrawEnv(void *env);

void SetDrawEnvironment(int a0) {
    long long *p;

    p = (long long *)((unsigned int)D_001321A0 | 0x20000000);
    func_00114020(p + 4, 0);
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
    p[3] = 0x47;
    p[2] = 0x20000;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
