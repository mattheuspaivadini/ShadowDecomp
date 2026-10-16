/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0187A8.s); this C
 * draft (Session 9) is kept for the record. */
struct S0187A8 {
    int f00;   /* 0x00 */
    int f04;   /* 0x04 */
    int f08;   /* 0x08 */
    int f0C;   /* 0x0C */
    int f10;   /* 0x10 */
    int f14;   /* 0x14 */
    int f18;   /* 0x18 */
    int f1C;   /* 0x1C */
    int f20;   /* 0x20 */
};

int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118578(int a0, int a1, int a2);

int sceInetAddress2Name(int a0, struct S0187A8 *p, int a2, int a3, int a4, int a5,
                  int a6, int a7, int a8) {
    int r;

    p->f00 = a2;
    p->f04 = a4;
    p->f08 = a6;
    p->f0C = a7;
    r = func_00118438(a0, (int)p, 4, a5, 0x10);
    if (r < 0)
        return r;
    p->f20 = 0;
    if (a2 & 0x80)
        p->f20 = a8;
    r = func_00118380(a0, 0x12, (int *)p, a3 + 0x20, 0x24);
    if (r < 0)
        return -0x21E;
    r = func_00118578(a3, (int)p, 8);
    if (r >= 0)
        return p->f00;
    return r;
}
