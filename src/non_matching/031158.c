/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 9 [cc=296].
 * R1 Phase A: 031158 variant (duplicated ld $s0)
 * The original .s stays in the build (asm/cod/031158.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo, non-small */

int func_00112088(int a0, int a1);

void func_00131158(int a0, int a1, int a2) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    if ((r = func_00112088(a1, a2)) == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
}
