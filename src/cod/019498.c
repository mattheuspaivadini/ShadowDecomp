/* asm/cod/019498.s -> func_00119498.
 * indexed copy loop after the RPC (Session 23)
 * MATCHED. */
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00119498(int a0, int *p, int *dst, int n, int a4) {
    int i;
    if (func_00118380(a0, a4, p, 0, n * 4 + 4) < 0) return -0x21E;
    for (i = 0; i < n; i++) dst[i] = p[i + 1];
    return p[0];
}
