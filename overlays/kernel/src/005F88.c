/* KERNEL.XFF @ 0x005F88 (84 B) - iosSPrintf
 * Evidence: EE varargs prologue (a2..t3 to the save area, f12..f19 to the FP save area) and vsprintf(buf, fmt, ap).
 */
#include <stdarg.h>
int vsprintf(char *buf, const char *fmt, va_list ap);

void iosSPrintf(char *buf, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
}
