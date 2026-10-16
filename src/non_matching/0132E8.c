/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 10 [cc=29].
 * R4 w25a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/0132E8.s); this C
 * draft (Session 8) is kept for the record. */
void sceVif1PkAlign(unsigned int **a0, int a1, int a2) {
    unsigned int mask;
    unsigned int *p;
    unsigned int *end;

    mask = 0xFFFFFFFFu >> (32 - ((a1 + 2) & 0x1F));
    p = (unsigned int *)*a0;
    end = (unsigned int *)(((unsigned int)p & ~mask) + ((unsigned int)a2 << 2));
    if (end < p)
        end = (unsigned int *)((unsigned int)end + 1 + mask);
    while (p < end) {
        *p = 0;
        p = p + 1;
        *a0 = p;
    }
}
/* func_001132E8 */
