/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 27 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01B670.s); this C
 * draft (Session 9) is kept for the record. */
int func_00107020(int a0);
int func_00107030(int a0);
extern int D_00151900[];
extern int D_00151E28[];

int func_0011B670(int a0, int *a1, int *a2) {
    if (D_00151900[1] == 0)
        return -1;
    if (a1 != 0)
        *a1 = D_00151900[1];
    if (a0 == 0) {
        func_00107020(D_00151E28[0]);
    } else if (func_00107030(D_00151E28[0]) < 0) {
        return 0;
    }
    if (a2 != 0)
        *a2 = D_00151900[2];
    if (a1 != 0)
        *a1 = D_00151900[1];
    D_00151900[1] = 0;
    return 1;
}
