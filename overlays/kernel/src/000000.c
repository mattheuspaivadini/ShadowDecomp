/* KERNEL.XFF @ 0x000000 (44 B) - _iosAssert
 * Evidence: tail call iosJumpRecoverPoint(.rodata+0x0 = the "assertion failed... at file:%s
 * line:%d" format, a0, a1, a2); the arguments shift one register right.
 */
extern char D_kernel_rodata_0000[];
void iosJumpRecoverPoint(const char *fmt, ...);

void _iosAssert(const char *file, int line, const char *expr) {
    iosJumpRecoverPoint(D_kernel_rodata_0000, file, line, expr);
}
