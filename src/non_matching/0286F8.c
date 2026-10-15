/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 15 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0286F8.s); this C
 * draft (Session 9) is kept for the record. */
int func_00128688(int a0);

int func_001286F8(int a0, unsigned int a1, int a2) {
    int *tbl;
    int old;

    if (a1 < 0x20) {
        tbl = *(int **)(a0 + 0x1D4);
        if (tbl == 0) {
            if (func_00128688(a0) != 0)
                return -1;
            tbl = *(int **)(a0 + 0x1D4);
        }
        old = tbl[a1];
        tbl[a1] = a2;
        return old;
    }
    *(int *)a0 = 0x16;
    return -1;
}
