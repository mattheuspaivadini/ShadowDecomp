/* KERNEL.XFF @ 0x01CC88 (84 B) - iosEntryLocaleFontNoLoad
 * Evidence: copies a 32-byte, byte-aligned record (ldl/ldr, sdl/sdr) into .bss+0x7C278, stores id over its word +8 and returns id. UNCONFIRMED: record layout.
 */
struct LocaleFont {
    char data[32];
};
extern struct LocaleFont D_kernel_bss_7C278;

int iosEntryLocaleFontNoLoad(int id, struct LocaleFont *font) {
    D_kernel_bss_7C278 = *font;
    *(int *)&D_kernel_bss_7C278.data[8] = id;
    return id;
}
