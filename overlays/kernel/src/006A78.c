/* KERNEL.XFF @ 0x006A78 (120 B) - iosJumpRecoverPoint
 * Evidence: vsprintf into the static buffer at .bss+0xD5C8, then LoaderSysJumpRecoverPoint(buffer).
 */
#include <stdarg.h>
extern char D_kernel_bss_D5C8[];
int vsprintf(char *buf, const char *fmt, va_list ap);
void LoaderSysJumpRecoverPoint(const char *msg);

void iosJumpRecoverPoint(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vsprintf(D_kernel_bss_D5C8, fmt, ap);
    va_end(ap);
    LoaderSysJumpRecoverPoint(D_kernel_bss_D5C8);
}
