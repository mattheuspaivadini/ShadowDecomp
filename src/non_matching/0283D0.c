/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 26 [cc=wine:ee-gcc2.95.2-273a].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0283D0.s); this C
 * draft (Session 9) is kept for the record. */
void *func_001283D0(void *dst, int c, unsigned int n) {
    unsigned char *d = (unsigned char *)dst;
    unsigned long long pat;

    if (n >= 8 && ((unsigned int)d & 0xF) == 0) {
        pat = (unsigned long long)(c & 0xFF);
        pat = pat | (pat << 8);
        pat = pat | (pat << 16);
        pat = pat | (pat << 32);
        while (n >= 0x20) {
            *(unsigned long long *)(d + 0x0) = pat;
            n -= 0x20;
            d += 0x10;
            *(unsigned long long *)(d + 0x0) = pat;
            d += 0x10;
        }
        while (n >= 8) {
            *(unsigned long long *)d = pat;
            n -= 8;
            d += 8;
        }
    }
    n -= 1;
    if (n != 0xFFFFFFFF) {
        do {
            *d++ = (unsigned char)c;
        } while (--n != 0xFFFFFFFF);
    }
    return dst;
}
