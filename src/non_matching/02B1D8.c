/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 45 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02B1D8.s); this C
 * draft (Session 9) is kept for the record. */
int func_0012B1D8(char *dst, int value, char prefix) {
    char  buf[0x134];
    char *p;
    char *out;
    int   v;
    int   neg;

    out = dst;
    *out = prefix;
    neg = value < 0;
    if (neg)
        value = -value;
    *++out = neg ? '-' : '+';
    out++;
    p = buf + sizeof(buf);
    if (value < 10) {
        *out++ = '0';
        *out++ = (char)(value + '0');
        return out - dst;
    }
    v = value;
    while (v >= 10) {
        *--p = (char)(v % 10) + '0';
        v /= 10;
    }
    *--p = (char)(v + '0');
    while (p < buf + sizeof(buf))
        *out++ = *p++;
    return out - dst;
}
