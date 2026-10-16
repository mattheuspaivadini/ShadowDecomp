/* asm/cod/02DA00.s -> func_0012D9C0.
 * 3x func_0012D7F0 init + 0x3C/0x38/0x1D8/0x1DC/0x1E0 stores; wave4c (R1)
 * MATCHED (Session 8). */
extern int _cleanup_r(void);
extern void func_0012D7F0(int a0, int a1, int a2, int a3);

void __sinit(int a0) {
    int *p = (int *)a0;
    int *q = (int *)(a0 + 0x1E4);

    p[0x3C / 4] = (int)_cleanup_r;
    p[0x38 / 4] = 1;
    func_0012D7F0((int)q, 4, 0, a0);
    func_0012D7F0(a0 + 0x23C, 9, 1, a0);
    func_0012D7F0(a0 + 0x294, 0xA, 2, a0);
    p[0x1D8 / 4] = 0;
    p[0x1E0 / 4] = (int)q;
    p[0x1DC / 4] = 3;
}
