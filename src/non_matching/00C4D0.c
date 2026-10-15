/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 23 [cc=29].
 * R2 w45a_2: reg-alloc (base pointers in $s0/$s2)
 * The original .s stays in the build (asm/cod/00C4D0.s); this C
 * draft (Session 8) is kept for the record. */
struct Sema10C4D0 {
    int   f00;      /* 0x00 */
    int   f04;      /* 0x04 */
    int   f08;      /* 0x08 */
    int   f0C;      /* 0x0C */
    int   f10;      /* 0x10 */
    void *f14;      /* 0x14 */
    char  pad18[8]; /* 0x18 */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00138070[];
extern int D_001459C0[];
extern int D_00146600[];
extern int D_001470C0[];

int func_0010A798(int a0);
int func_0010A8C0(void);
int func_0010A7C8(void);
int func_00106FE0(void *args);
int func_00106FF0(int a0);
int func_00107020(int a0);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);

int sceStdioAddDrv(int a0) {
    struct Sema10C4D0 buf;
    int out;
    int h;
    int r;

    func_0010A798(0xF);
    if (D_00132314 == 0)
        func_0010A8C0();
    D_001459C0[3] = a0;
    buf.f04 = 1;
    buf.f14 = D_00138070;
    buf.f08 = 0;
    h = func_00106FE0(&buf);
    D_001459C0[0] = h;
    D_001459C0[1] = (int)&out;
    D_001459C0[2] = 4;
    r = func_0010A228((int)D_001470C0, 0xF, 0, (int)D_001459C0, 0x10,
                      (int)D_00146600, 4, 0, 0, 0);
    if (r < 0) {
        func_00106FF0(h);
        func_0010A7C8();
        return -0xB;
    }
    r = *(int *)((unsigned int)D_00146600 | 0x20000000);
    func_0010A7C8();
    if (r == 0) {
        func_00106FF0(h);
        return -0xB;
    }
    func_00107020(h);
    func_00106FF0(h);
    return out;
}
