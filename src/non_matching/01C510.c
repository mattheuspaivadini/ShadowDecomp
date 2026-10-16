/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 9 [cc=29].
 * error-code unbox block layout
 * The original .s stays in the build (asm/cod/01C510.s); this C
 * draft (Session 8) is kept for the record. */
int func_0011C4C8(int a0, int a1, int *a2);

int func_0011C510(int a0, int a1, int *a2) {
    unsigned int r = func_0011C4C8(a0, a1, a2);

    if (*a2 != 0)
        return 0;
    if (r != 0xFFFFFFFFU)
        return r & 0x7FFFFFFF;
    *a2 = 0x81010059;
    return 0xFFFFFFFFU;
}
