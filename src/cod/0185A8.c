/* asm/cod/0185A8.s -> func_00118438.
 * 018xxx record-put family (p[1]/p[0] order, n = a3*8, n|4)
 * MATCHED (Session 8). */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int a1, int *p, int a3, int a4);

int func_001185A8(int a0, int *p, int a2, int a3, int a4) {
    int n;
    int r;

    n = a3 * 8;
    p[1] = a4;
    p[0] = a3;
    r = func_00118438(a0, (int)p, 2, a2, n);
    if (r < 0)
        return r;
    r = func_00118380(a0, 0x14, p, n + 8, n | 4);
    if (r < 0)
        return -0x21E;
    r = func_00118490(a0, a2, p, 2, n);
    if (r < 0)
        return r;
    return p[0];
}
