/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 5 [cc=29].
 * return r on the 0xFFFFFFFF path reproduces the lui/ori; residual = r lives in $a0 in the original (load of *a2 before the move)
 * The original .s stays in the build (asm/cod/01C510.s); this C
 * draft (Session 23) is kept for the record. * Session 23 step 3: permute_types.py --pairs --locals (struct members, externs, locals and parameters) - all variants tie, so the residual is not type-driven.
 */
int func_0011C4C8(int a0, int a1, int *a2);
int func_0011C510(int a0, int a1, int *a2) {
    unsigned int r = func_0011C4C8(a0, a1, a2);
    if (*a2 != 0) return 0;
    if (r == 0xFFFFFFFFU) { *a2 = 0x81010059; return r; }
    return r & 0x7FFFFFFF;
}
