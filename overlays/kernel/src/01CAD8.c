/* KERNEL.XFF @ 0x01CAD8 (40 B) - iosGetFontIDWithJIS
 * Evidence: (jis >> 8) * 94 + (jis & 0xFF) - 0xC3F: row/cell of a JIS X 0208 code to a linear glyph index (94 cells per row; 0xC3F = 0x21*94 + 0x21).
 */
int iosGetFontIDWithJIS(int jis) {
    return (jis >> 8) * 94 + (jis & 0xFF) - 0xC3F;
}
