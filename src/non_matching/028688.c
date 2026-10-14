/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 2 [cc=296].
 * rotated constant-trip clear loop; wave3d (R1)
 * The original .s stays in the build (asm/cod/028688.s); this C
 * draft (Session 8) is kept for the record. */
int func_00127A60(int a0, int a1);

int func_00128688(int a0) {
    int *p;
    int r;
    int i;
    int *q;

    p = (int *)a0;
    if (p[0x75] != 0)
        return 0;
    r = func_00127A60(a0, 0x80);
    p[0x75] = r;
    if (r == 0)
        return -1;
    q = (int *)(r + 0x7C);
    for (i = 0x1F; i >= 0; i--) {
        *q = 0;
        q--;
    }
    return 0;
}
