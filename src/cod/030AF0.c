/* asm/cod/030AF0.s -> func_00130AC8.
 * Session 11a: empty-asm +r pin keeps the return value in a register before the tail call
 * MATCHED (Session 8). */
int strtod(int a0);
int dptofp(int x);

int strtodf(int a0) {
    int v = strtod(a0);

    asm volatile ("" : "+r" (v));
    return dptofp(v);
}
