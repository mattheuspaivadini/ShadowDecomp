/* asm/cod/019708.s -> func_00119708.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
int func_00119548(int a0, int a1, int a2, int a3);
int func_00119648(int a0, int a1, int a2, int a3);

int func_00119708(int a0, int a1, int a2, int a3, int a4) {
    int r;
    int st;

    r = func_00119548(a0, a1, a2, a3);
    if (r < 0)
        return r;
    r = func_00119648(a0, a1, *(int *)a2, a4);
    st = 0;
    if (r <= -1)
        st = r;
    return st;
}
