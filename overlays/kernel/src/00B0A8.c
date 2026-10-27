/* KERNEL.XFF @ 0x00B0A8 (84 B) - DldExceptionByOriginAdr
 * Evidence: the static at .text+0xAF40 maps the faulting address to a name; iosJumpRecoverPoint(.rodata+0xF68, name, adr) when found, else iosJumpRecoverPoint(.rodata+0x1010, adr).
 */
extern char D_kernel_rodata_0F68[];
extern char D_kernel_rodata_1010[];
const char *func_00AF40(void *adr);
void iosJumpRecoverPoint(const char *fmt, ...);

void DldExceptionByOriginAdr(void *adr) {
    const char *name = func_00AF40(adr);

    if (name != 0) {
        iosJumpRecoverPoint(D_kernel_rodata_0F68, name, adr);
    } else {
        iosJumpRecoverPoint(D_kernel_rodata_1010, adr);
    }
}
