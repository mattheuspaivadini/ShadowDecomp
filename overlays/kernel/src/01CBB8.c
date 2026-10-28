/* KERNEL.XFF @ 0x01CBB8 (204 B) - iosGetFontIDWithEUC
 * Evidence: the static EUC converter at .text+0x1C200 followed by an inlined copy of iosGetFontIDWithSJIS (same TU, identical body). UNCONFIRMED: static name.
 */
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

int iosGetFontIDWithEUC(int code) {
    return iosGetFontIDWithSJIS(func_01C200(code));
}
