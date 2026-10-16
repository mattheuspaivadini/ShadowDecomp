/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 10 [cc=29].
 * sceVif1PkAlign: *a0 = ++p loop-hoisting vs per-iteration store
 * The original .s stays in the build (asm/cod/0132E8.s); this C
 * draft (Session 12) is kept for the record. */
void sceVif1PkAlign(unsigned int **a0, int a1, int a2) {
    unsigned int mask;
    unsigned int *p;
    unsigned int *end;

    mask = 0xFFFFFFFFu >> (32 - ((a1 + 2) & 0x1F));
    p = *a0;
    end = (unsigned int *)(((unsigned int)p & ~mask) + (a2 << 2));
    if (end < p)
        end = (unsigned int *)((unsigned int)end + 1 + mask);
    while (p < end) {
        *p = 0;
        p = p + 1;
        *a0 = p;
        __asm__ __volatile__("" ::: "memory");
    }
}
