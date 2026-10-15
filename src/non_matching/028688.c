/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 2 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/028688.s); this C
 * draft (Session 9) is kept for the record. */
int func_00127A60(int a0, int a1);

int func_00128688(int a0) {
    int *p;
    int *q;
    int r;
    int i;

    p = (int *)a0;
    if (p[0x75] != 0)
        return 0;
    r = func_00127A60(a0, 0x80);
    p[0x75] = r;
    if (r == 0)
        return -1;
    q = (int *)(r + 0x7C);
    i = 0x1F;
    do {
        i--;
        *q = 0;
        q--;
    } while (i >= 0);
    return 0;
}
