/* KERNEL.XFF @ 0x01CB00 (180 B) - iosGetFontIDWithSJIS
 * Evidence: Shift-JIS to JIS X 0208 (lead 0x81..0x9F - 0x81 / 0xE0..0xEF - 0xC1, doubled; trail 0x40..0x7E - 0x40, 0x80..0x9E - 0x41, 0x9F..0xFC - 0x9F with lead + 1; jis = ((lead + 1) << 8) + trail + 0x2021) in 64-bit arithmetic, then the font cell index row * 94 + cell - 0xC3F (as iosGetFontDataWithJIS).
 */
int iosGetFontIDWithSJIS(int code) {
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
