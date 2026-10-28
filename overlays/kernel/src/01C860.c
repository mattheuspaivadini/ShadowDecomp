/* KERNEL.XFF @ 0x01C860 (292 B) - iosGetFontDataWithSJIS
 * Evidence: inlined Shift-JIS to JIS conversion (as iosGetFontIDWithSJIS) feeding an inlined copy of iosGetFontDataWithJIS (same TU); returns the glyph pointer and optionally copies the font record. Ghidra/REA dossier (r5900 language) used as the structural hint.
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

static __inline__ int iosConvertSJIStoJIS(int code) {
    long hi = (code >> 8) & 0xFF;
    long lo = code & 0xFF;

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
    return ((hi + 1) << 8) + lo + 0x2021;
}

static __inline__ char *iosGetFontDataWithJIS(struct iosFont *info, int code, int font) {
    int hi = code >> 8;
    int lo = code & 0xFF;
    struct iosFont *f = &D_kernel_bss_7C278[font];
    char *data = f->data + (hi * 94 + lo - 0xC3F) * (f->w * f->h);

    if (info) {
        *info = *f;
    }
    return data;
}

char *iosGetFontDataWithSJIS(struct iosFont *info, int code, int font) {
    return iosGetFontDataWithJIS(info, iosConvertSJIStoJIS(code), font);
}
