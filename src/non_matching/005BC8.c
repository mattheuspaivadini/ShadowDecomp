/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 14 [cc=296].
 * R2 w45a_1: shape of matched 006518/006310
 * The original .s stays in the build (asm/cod/005BC8.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_0013A138;     /* .sdata/.sbss scalar (%gp_rel) */
extern int  D_0013A13C;     /* .sdata/.sbss scalar (%gp_rel) */
extern int  D_0013A140;     /* .sdata/.sbss scalar (%gp_rel) */
extern char D_0013EB60[];   /* lui/%lo */
extern int  D_001321A0[];   /* lui/%lo, address ORed with 0x20000000 */

int  func_00107260(int x);
int  sceGsSyncPath(int mode, int timeout);
int  func_00113B60(int a0);
int  func_00113B00(int p, int flag);
int  func_00114080(void *dst, int a1, int a2, short a3);
int  sceGsPutDrawEnv(void *env);
int  func_00114020(long long *p, short a1);

void func_00105BC8(void) {
    char *p;
    long long *q;

    func_00107260(0);
    sceGsSyncPath(1, 0);
    D_0013A140 = func_00113B60(0);
    D_0013A13C = D_0013A13C + 1;
    D_0013A138 = D_0013A13C & 1;
    func_00113B00((int)D_0013EB60, D_0013A138);
    p = (char *)((unsigned int)D_0013EB60 | 0x20000000);
    if (D_0013A138 != 0) {
        func_00114080(p + 0x150, 0x800, 0x800, (short)D_0013A140);
        sceGsPutDrawEnv(p + 0x140);
    } else {
        func_00114080(p + 0x60, 0x800, 0x800, (short)D_0013A140);
        sceGsPutDrawEnv(p + 0x50);
    }
    q = (long long *)((unsigned int)D_001321A0 | 0x20000000);
    func_00114020(q + 4, 0);
    q[4] = 0x44;
    q[3] = 0x47;
    q[2] = 0x20000;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(q);
}
