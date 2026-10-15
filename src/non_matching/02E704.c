/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 65 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02E704.s); this C
 * draft (Session 9) is kept for the record. */
void *func_0012E704(void *p, int c, unsigned int n) {
    unsigned char *q;
    unsigned char  cc;
    unsigned int   i;

    q = (unsigned char *)p;
    cc = (unsigned char)c;
    if (n >= 0x10 && ((unsigned int)q & 0xF) == 0) {
        unsigned long long pat;
        unsigned long long ones;
        unsigned long long high;

        pat = (unsigned long long)cc * 0x0101010101010101ULL;
        ones = 0x0101010101010101ULL;
        high = 0x8080808080808080ULL;
        while (n >= 0x10) {
            unsigned long long w0;
            unsigned long long w1;
            unsigned long long x0;
            unsigned long long x1;

            w0 = ((unsigned long long *)q)[0];
            w1 = ((unsigned long long *)q)[1];
            x0 = w0 ^ pat;
            x1 = w1 ^ pat;
            if ((((x0 - ones) & ~x0 & high)
                 | ((x1 - ones) & ~x1 & high)) != 0)
                break;
            n -= 0x10;
            q += 0x10;
        }
    }
    for (i = n - 1; i != (unsigned int)-1; i--) {
        if (*q == cc)
            return q;
        q++;
    }
    return 0;
}
