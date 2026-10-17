/* asm/cod/018490.s -> func_00118490.
 * bounded memcpy out of a word-indexed buffer; twin of 018438 (Session 19)
 * MATCHED. */
void *func_0012821C(void *dst, const void *src, int n);

int func_00118490(int *p, void *a1, int a2, int a3, int a4) {
    int off = a3 << 2;
    int lim = p[12] - off;

    if (a1 != 0) {
        if (a4 < 0 || lim < a4)
            return -0x21F;
        func_0012821C(a1, (void *)(off + a2), a4);
    }
    return 0;
}
