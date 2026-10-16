/* STATUS (10, 2026-10-16): NON_MATCHING. best score 4 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/031218.s); this C
 * draft (10) is kept for the record. */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo, non-small */

int func_00111F18(int a0, int a1, int a2);

int _read_r(int a0, int a1, int a2, int a3) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    if ((r = func_00111F18(a1, a2, a3)) == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
    return r;
}
