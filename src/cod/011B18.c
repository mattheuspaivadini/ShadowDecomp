/* asm/cod/011B18.s -> sceSifSetRebootNotifyBuffer.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
int DIntr(void);
int EIntr(void);
int func_001283D0(void *dst, int value, int size);

extern int D_00133938[];
extern int D_0013393C[];

int sceSifSetRebootNotifyBuffer(int a0, int a1) {
    int g;
    int old;

    g = DIntr();
    old = D_00133938[0];
    D_00133938[0] = a0;
    D_0013393C[0] = a1;
    func_001283D0((void *)a0, 0, a1 << 4);
    if (g != 0)
        EIntr();
    return old;
}
