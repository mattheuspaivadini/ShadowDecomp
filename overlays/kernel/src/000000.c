/* KERNEL.XFF @ 0x000000 (44 B) - _iosAssert
 * Evidence: tail call iosJumpRecoverPoint(.rodata+0x0 "assertion failed...
 */
extern char D_kernel_rodata_0000[];
void iosJumpRecoverPoint(const char *fmt, ...);

void _iosAssert(const char *file, int line, const char *expr) {
    iosJumpRecoverPoint(D_kernel_rodata_0000, file, line, expr);
}
