/* asm/cod/030AF0.s -> func_00130AC8.
 * Session 11a: empty-asm +r pin keeps the return value in a register before the tail call
 * MATCHED (Session 8). */
int func_00130AC8(int a0);
int func_001258A0(int x);

int func_00130AF0(int a0) {
    int v = func_00130AC8(a0);

    asm volatile ("" : "+r" (v));
    return func_001258A0(v);
}
