/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 55 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0282CC.s); this C
 * draft (Session 9) is kept for the record. */
void *func_001282CC(void *dst, const void *src, unsigned int n) {
    char       *d;
    const char *s;
    int         i;

    d = (char *)dst;
    s = (const char *)src;
    if (s < d && d < s + n) {
        d += n;
        s += n;
        for (i = n - 1; i != -1; i--)
            *--d = *--s;
        return dst;
    }
    for (i = n - 1; i != -1; i--)
        *d++ = *s++;
    return dst;
}
