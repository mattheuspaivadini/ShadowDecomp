/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 52 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02BF48.s); this C
 * draft (Session 9) is kept for the record. */
char *__sccl(unsigned char *tbl, char *s) {
    char c;
    char prev;
    char end;
    int  neg;
    int  v;
    int  i;

    c = *s;
    if (c == '^') {
        neg = 1;
        s++;
        c = *s;
        s++;
    } else {
        neg = 0;
    }
    for (i = 0xFF; i >= 0; i--)
        tbl[i] = (unsigned char)neg;
    v = 1 - neg;
    if (c == 0)
        return s - 1;
    prev = c;
    for (;;) {
        tbl[prev] = (unsigned char)v;
        c = *s;
        s++;
        if (c == '-') {
            end = *s;
            if (end == ']' || end < prev) {
                prev = '-';
                continue;
            }
            s++;
            do {
                prev++;
                tbl[prev] = (unsigned char)v;
            } while (prev < end);
            c = *s;
        } else if (c < 0x2E) {
            if (c == 0)
                return s - 1;
            prev = c;
            continue;
        } else if (c == ']') {
            return s;
        }
        prev = c;
    }
}
/* func_0012BF48 */
