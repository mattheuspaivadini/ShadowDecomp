/* KERNEL.XFF @ 0x01C750 (120 B) - iosGetFontDataWithID
 * Evidence: font record [id] (32 bytes at .bss+0x7C278): returns bitmap (+8) + code * (w (+0x10) * h (+0x14)) and, when out is non-NULL, copies the byte-aligned 32-byte record to it (ldl/ldr, sdl/sdr). UNCONFIRMED: field names.
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

char *iosGetFontDataWithID(struct LocaleFont *out, int code, int id) {
    struct LocaleFontInfo *f = &D_kernel_bss_7C278[id];
    char *p = f->bitmap + code * (f->w * f->h);

    if (out != 0) {
        *out = *(struct LocaleFont *)f;
    }
    return p;
}
