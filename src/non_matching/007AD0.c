/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 66 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/007AD0.s); this C
 * draft (Session 9) is kept for the record. */
typedef unsigned int u_long128V2 __attribute__((mode(TI)));

struct P07AD0 {
    u_long128V2 q000;   /* 0x000 */
    u_long128V2 q010;   /* 0x010 */
    u_long128V2 q020;   /* 0x020 */
    u_long128V2 q030;   /* 0x030 */
    u_long128V2 q040;   /* 0x040 */
    u_long128V2 q050;   /* 0x050 */
    u_long128V2 q060;   /* 0x060 */
    u_long128V2 q070;   /* 0x070 */
    u_long128V2 q080;   /* 0x080 */
    u_long128V2 q090;   /* 0x090 */
    u_long128V2 q0A0;   /* 0x0A0 */
    u_long128V2 q0B0;   /* 0x0B0 */
    u_long128V2 q0C0;   /* 0x0C0 */
    u_long128V2 q0D0;   /* 0x0D0 */
    u_long128V2 q0E0;   /* 0x0E0 */
    u_long128V2 q0F0;   /* 0x0F0 */
    u_long128V2 q100;   /* 0x100 */
    u_long128V2 q110;   /* 0x110 */
    u_long128V2 q120;   /* 0x120 */
    u_long128V2 q130;   /* 0x130 */
    u_long128V2 q140;   /* 0x140 */
    u_long128V2 q150;   /* 0x150 */
    u_long128V2 q160;   /* 0x160 */
    u_long128V2 q170;   /* 0x170 */
    u_long128V2 q180;   /* 0x180 */
    u_long128V2 q190;   /* 0x190 */
    u_long128V2 q1A0;   /* 0x1A0 */
    u_long128V2 q1B0;   /* 0x1B0 */
    long long   q1C0;   /* 0x1C0 low 32 bits kept */
    long long   q1C8;   /* 0x1C8 */
    long long   q1D0;   /* 0x1D0 low 32 bits kept */
    long long   q1D8;   /* 0x1D8 */
    long long   q1E0;   /* 0x1E0 low 32 bits kept */
    long long   q1E8;   /* 0x1E8 */
    long long   q1F0;   /* 0x1F0 low 32 bits kept */
    long long   q1F8;   /* 0x1F8 */
    u_long128V2 q200;   /* 0x200 */
    u_long128V2 q210;   /* 0x210 */
    u_long128V2 q220;   /* 0x220 */
    u_long128V2 q230;   /* 0x230 */
    u_long128V2 q240;   /* 0x240 */
    u_long128V2 q250;   /* 0x250 */
    u_long128V2 q260;   /* 0x260 */
    u_long128V2 q270;   /* 0x270 */
};

extern int func_00107460(void);
extern int func_0010FB20(void);
extern int func_0010FB70(void);
extern int func_00106EE0(int a0, int *buf);
extern int func_00106E00(int a0, int a1);

int func_00107AD0(int a0, int a1) {
    int buf[4];
    int r;
    struct P07AD0 *p;

    if (func_00107460() != 0)
        return -1;
    if (func_0010FB20() == 0)
        return -1;
    r = func_00106EE0(a0, buf);
    if (r < 0) {
        func_0010FB70();
        return r;
    }
    if (buf[0] != 0x10) {
        func_0010FB70();
        return -1;
    }
    p = (struct P07AD0 *)(buf[2] + buf[3] - 0x2A0);
    p->q000 = 0; p->q010 = 0; p->q020 = 0; p->q030 = 0;
    p->q040 = 0; p->q050 = 0; p->q060 = 0; p->q070 = 0;
    p->q080 = 0; p->q090 = 0; p->q0A0 = 0; p->q0B0 = 0;
    p->q0C0 = 0; p->q0D0 = 0; p->q0E0 = 0; p->q0F0 = 0;
    p->q100 = 0; p->q110 = 0; p->q120 = 0; p->q130 = 0;
    p->q140 = 0; p->q150 = 0; p->q160 = 0; p->q170 = 0;
    p->q180 = 0; p->q190 = 0; p->q1A0 = 0; p->q1B0 = 0;
    p->q1C0 = (long long)*(int *)((char *)p + 0x1C0);
    p->q1C8 = 0;
    p->q1D0 = (long long)*(int *)((char *)p + 0x1D0);
    p->q1D8 = 0;
    p->q1E0 = (long long)*(int *)((char *)p + 0x1E0);
    p->q1E8 = 0;
    p->q1F0 = (long long)*(int *)((char *)p + 0x1F0);
    p->q1F8 = 0;
    p->q200 = 0; p->q210 = 0; p->q220 = 0; p->q230 = 0;
    p->q240 = 0; p->q250 = 0; p->q260 = 0; p->q270 = 0;
    *(long long *)((char *)p + 0x40) = a1;
    func_0010FB70();
    return func_00106E00(a0, a1);
}
