/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 5 [cc=29].
 * R4 w25a_1: publishes D_00133938/D_0013393C then fill
 * The original .s stays in the build (asm/cod/011B18.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010FB20(void);
int func_0010FB70(void);
int func_001283D0(void *dst, int value, int size);

extern int D_00133938[];
extern int D_0013393C[];

int func_00111B18(int a0, int a1) {
    int g;
    int old;

    g = func_0010FB20();
    old = D_00133938[0];
    D_0013393C[0] = a1;
    D_00133938[0] = a0;
    func_001283D0((void *)a0, 0, a1 << 4);
    if (g != 0)
        func_0010FB70();
    return old;
}
