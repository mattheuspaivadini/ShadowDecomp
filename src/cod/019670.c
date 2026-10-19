/* asm/cod/019670.s -> func_00119670.
 * Callee arity from the matched callees (func_00119568 takes 3 args); the 3-arg call fixes the prologue copy order, if (r < 0) return r keeps the slt/movn tail (Session 28).
 * MATCHED. */
int func_00119568(int a0, int a1, int *out);
int func_00119548(int a0, int a1, int *out, int a3);
int func_00119648(int a0, int a1, int a2, int a3);

int func_00119670(int a0, int a1, int *a2, int a3, int a4) {
    int r;

    if (func_00119568(a0, a1, a2) < 0) {
        r = func_00119548(a0, a1, a2, a3);
        if (r < 0)
            return r;
    }
    r = func_00119648(a0, a1, *a2, a4);
    if (r < 0)
        return r;
    return 0;
}
