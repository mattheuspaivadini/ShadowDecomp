/* KERNEL.XFF @ 0x016178 (60 B) - iosGsInitDC
 * Evidence: iosResetDC(&dcs[iosDlGetWorkBufId()]) with a 400-byte element (id*25*16) off the pointer at .bss+0x1F098. UNCONFIRMED: element type.
 */
struct DC {
    char data[400];
};
extern struct DC *D_kernel_bss_1F098;
int iosDlGetWorkBufId(void);
void iosResetDC(struct DC *dc);

void iosGsInitDC(void) {
    iosResetDC(&D_kernel_bss_1F098[iosDlGetWorkBufId()]);
}
