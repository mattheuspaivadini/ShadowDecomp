/* KERNEL.XFF @ 0x01C530 (204 B) - iosConvertStringEUCtoSJIS
 * Evidence: strlen(src); for each byte, an EUC lead byte (c + 0x5F, 8-bit, < 0x5E) pulls the next byte too (lo | hi << 8) through the static EUC->SJIS converter .text+0x1C200 and stores the result big-endian (dst[0] = hi, dst[1] = lo), otherwise the byte is copied; dst[len] = 0; returns len / 2. UNCONFIRMED: names.
 * Levers: unsigned char src; if (len > 0) { p = dst; do {...} while (i < len); } puts the p = dst copy after the blez; empty asm memory clobber in the kanji arm keeps the second src[i] load (no CSE with c).
 * c_sources: 01C530 = src/01C530.c -G0 -fno-strict-aliasing
 */
extern unsigned int strlen(const char *s);
unsigned int func_01C200(unsigned int c);

int iosConvertStringEUCtoSJIS(char *dst, unsigned char *src) {
    int len;
    int i;
    char *p;
    unsigned int sj;

    len = strlen((char *)src);
    i = 0;
    if (len > 0) {
        p = dst;
        do {
            unsigned char c = src[i];

            if ((unsigned char)(c + 0x5F) < 0x5E) {
                __asm__("" ::: "memory");
                sj = func_01C200(src[i] | (src[i + 1] << 8)) & 0xFFFF;
                i++;
                p[1] = sj;
                p[0] = sj >> 8;
                p++;
            } else {
                p[0] = c;
            }
            p++;
            i++;
        } while (i < len);
    }
    dst[len] = 0;
    return len / 2;
}
