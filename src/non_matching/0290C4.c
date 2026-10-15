/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 72 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0290C4.s); this C
 * draft (Session 9) is kept for the record. */
int func_001290C4(char *s) {
    char *p = s;

    while (*p != 0)
        p++;
    return p - s;
}
