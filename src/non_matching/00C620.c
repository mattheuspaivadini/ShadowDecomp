/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 17 [cc=29].
 * R2 w45a_2: reg-alloc ($s1 reused as node index)
 * The original .s stays in the build (asm/cod/00C620.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00132314 __attribute__((section(".data")));
extern int D_00132320 __attribute__((section(".data")));
extern char D_00146EC0[];

int func_0010A798(int a0);
int sceFsInit(void);
int func_0010A7C8(void);
int func_0010A1A0(void);
int sceStdioCCode(int a0, int a1);
int WaitSema(int a0);
int SignalSema(int a0);

int sceDopen(int a0) {
    int *h;
    int r;

    func_0010A798(9);
    if (D_00132314 == 0)
        sceFsInit();
    func_0010A7C8();
    h = (int *)func_0010A1A0();
    if (h == 0)
        return -0x13;
    r = sceStdioCCode(a0, 9);
    if (r < 0) {
        WaitSema(D_00132320);
        h[1] = 0;
    } else {
        WaitSema(D_00132320);
        h[0] = r;
        r = (int)((int)h - (int)D_00146EC0) >> 4;
    }
    SignalSema(D_00132320);
    return r;
}
