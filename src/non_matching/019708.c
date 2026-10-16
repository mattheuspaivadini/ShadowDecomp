/* STATUS (10, 2026-10-16): NON_MATCHING. best score 4 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/019708.s); this C
 * draft (10) is kept for the record. */
int func_00119548(int a0, int a1, int a2, int a3);
int func_00119648(int a0, int a1, int a2, int a3);

int func_00119708(int a0, int a1, int a2, int a3, int a4) {
    int r;

    r = func_00119548(a0, a1, a2, a3);
    if (r < 0)
        return r;
    r = func_00119648(a0, a1, *(int *)a2, a4);
    if (r >= 0)
        r = 0;
    return r;
}
