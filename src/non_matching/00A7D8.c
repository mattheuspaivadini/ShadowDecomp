/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 27 [cc=29].
 * R4 w25a_1: dual base for D_00147140 + $gp inline-asm store
 * The original .s stays in the build (asm/cod/00A7D8.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010A798(int a0);
int sceFsInit(void);
int func_0010A7C8(void);
int DIntr(void);
int EIntr(void);

extern int D_00132314[];
extern int D_00147140[];
extern int D_00147180[];

int scePowerOffHandler(int a0, int a1) {
    int g;
    int old;

    func_0010A798(0x1B);
    if (D_00132314[0] == 0)
        sceFsInit();
    g = DIntr();
    old = D_00147140[0];
    D_00147140[1] = a1;
    D_00147140[0] = a0;
    __asm__ __volatile__("sw $gp, %0" ::"m"(D_00147180[0]) : "memory");
    if (g != 0)
        EIntr();
    func_0010A7C8();
    return old;
}
