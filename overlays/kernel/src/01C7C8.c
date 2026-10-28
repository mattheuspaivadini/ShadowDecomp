/* KERNEL.XFF @ 0x01C7C8 (152 B) - iosGetFontDataWithJIS
 * Evidence: JIS row = code >> 8, cell = code & 0xFF; returns font[n].data (+8) + (row * 94 + cell - 0xC3F) * (w * h) (+0x10, +0x14) for the 0x20-byte font records at .bss+0x7C278; a non-NULL info gets the whole record (unaligned 8-byte struct copy). UNCONFIRMED: field names.
 */
struct iosFont {
    int unk0;
    int unk4;
    char *data;
    int unkC;
    int w;
    int h;
    int unk18;
    int unk1C;
};
extern struct iosFont D_kernel_bss_7C278[];

char *iosGetFontDataWithJIS(struct iosFont *info, int code, int font) {
    int hi = code >> 8;
    int lo = code & 0xFF;
    struct iosFont *f = &D_kernel_bss_7C278[font];
    char *data = f->data + (hi * 94 + lo - 0xC3F) * (f->w * f->h);

    if (info) {
        *info = *f;
    }
    return data;
}
