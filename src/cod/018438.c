/* asm/cod/018438.s -> func_00118438.
 * bounded memcpy into a word-indexed buffer; offset + base (int) operand order (Session 19)
 * MATCHED. */
void *func_0012821C(void *dst, const void *src, int n);

int func_00118438(int *p, int a1, int a2, const void *a3, int a4) {
    int off = a2 << 2;
    int lim = p[12] - off;

    if (a3 != 0) {
        if (a4 < 0 || lim < a4)
            return -0x21F;
        func_0012821C((void *)(off + a1), a3, a4);
    }
    return 0;
}
