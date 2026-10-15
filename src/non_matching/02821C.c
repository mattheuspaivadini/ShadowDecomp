/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 26 [cc=wine:ee-gcc2.95.2-273a].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02821C.s); this C
 * draft (Session 9) is kept for the record. */
void *func_0012821C(void *dst, const void *src, unsigned int n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    if (n >= 0x20 && ((((unsigned int)d | (unsigned int)s) & 0xF) == 0)) {
        do {
            *(unsigned long long *)(d + 0x0) = *(const unsigned long long *)(s + 0x0);
            n -= 0x20;
            s += 0x10;
            d += 0x10;
            *(unsigned long long *)(d + 0x0) = *(const unsigned long long *)(s + 0x0);
            s += 0x10;
            d += 0x10;
        } while (n >= 0x20);
    }
    if (n >= 8) {
        do {
            *(unsigned long long *)d = *(const unsigned long long *)s;
            n -= 8;
            s += 8;
            d += 8;
        } while (n >= 8);
    }
    n -= 1;
    if (n != 0xFFFFFFFF) {
        do {
            *d++ = *s++;
        } while (--n != 0xFFFFFFFF);
    }
    return dst;
}
