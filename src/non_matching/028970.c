/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 9 [cc=296].
 * R1 Phase A: func_001120A8 variant
 * The original .s stays in the build (asm/cod/028970.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo, non-small */

int func_001120A8(int a0, int a1);

void func_00128970(int a0, int a1, int a2) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    if ((r = func_001120A8(a1, a2)) == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
}
