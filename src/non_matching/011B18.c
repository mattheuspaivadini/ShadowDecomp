/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/011B18.s); this C
 * draft (10) is kept for the record. */
int func_0010FB20(void);
int func_0010FB70(void);
int func_001283D0(void *dst, int value, int size);

extern int D_00133938[];
extern int D_0013393C[];

int sceSifSetRebootNotifyBuffer(int a0, int a1) {
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
