/* KERNEL.XFF @ 0x01C600 (312 B) - iosConvertStringEUCtoID
 * Evidence: for every 2-byte EUC code (aligned u16 read) of the strlen-long source: the static EUC->SJIS converter at .text+0x1C200, then the inlined SJIS font cell index stored as a short at dst + i; dst[len] = 0; returns len / 2.
 */
unsigned int strlen(const char *s);
int func_01C200(int code);

static __inline__ int iosGetFontIDWithSJIS(int code) {
    long hi = (code >> 8) & 0xFF;
    long lo = code & 0xFF;
    int jis;

    if (hi >= 0x81 && hi <= 0x9F) {
        hi -= 0x81;
    } else if (hi >= 0xE0 && hi <= 0xEF) {
        hi -= 0xC1;
    }
    hi <<= 1;
    if (lo >= 0x40 && lo <= 0x7E) {
        lo -= 0x40;
    } else if (lo >= 0x80 && lo <= 0x9E) {
        lo -= 0x41;
    } else if (lo >= 0x9F && lo <= 0xFC) {
        lo -= 0x9F;
        hi++;
    }
    jis = ((hi + 1) << 8) + lo + 0x2021;
    return (jis >> 8) * 94 + (jis & 0xFF) - 0xC3F;
}

int iosConvertStringEUCtoID(char *dst, unsigned char *src) {
    int len = strlen((char *)src);
    int i;

    for (i = 0; i < len; i += 2) {
        *(short *)(dst + i) = iosGetFontIDWithSJIS(func_01C200(*(unsigned short *)(src + i)));
    }
    dst[len] = 0;
    return len / 2;
}
