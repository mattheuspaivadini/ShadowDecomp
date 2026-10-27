/* KERNEL.XFF @ 0x01CCE0 (140 B) - iosGetFontInfo
 * Evidence: copies the 32-byte font record [id] to out with unaligned ld/sd pairs addressed from the symbol (lui/addu per half).
 */
struct LocaleFont {
    char data[32];
};
struct LocaleFontInfo {
    int unk0;
    int unk4;
    char *bitmap;
    int unkC;
    int w;
    int h;
    int unk18;
    int unk1C;
};
extern struct LocaleFontInfo D_kernel_bss_7C278[];

void iosGetFontInfo(struct LocaleFont *out, int id) {
    *out = *(struct LocaleFont *)&D_kernel_bss_7C278[id];
}
