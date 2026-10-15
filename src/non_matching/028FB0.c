/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 66 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/028FB0.s); this C
 * draft (Session 9) is kept for the record. */
char *func_00128FB0(char *dst, char *src) {
    char *d = dst;

    while ((*d = *src) != 0) {
        d++;
        src++;
    }
    return dst;
}
