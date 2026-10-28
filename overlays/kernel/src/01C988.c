/* KERNEL.XFF @ 0x01C988 (336 B) - iosGetFontDataWithEUC
 * Evidence: the static EUC converter at .text+0x1C200 feeding an inlined copy of iosGetFontDataWithSJIS (itself SJIS->JIS + iosGetFontDataWithJIS inlined), as iosGetFontIDWithEUC does for the ID.
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

static __inline__ char *iosGetFontDataWithSJIS(struct iosFont *info, int code, int font) {
    return iosGetFontDataWithJIS(info, iosConvertSJIStoJIS(code), font);
}

int func_01C200(int code);

char *iosGetFontDataWithEUC(struct iosFont *info, int code, int font) {
    return iosGetFontDataWithSJIS(info, func_01C200(code), font);
}
