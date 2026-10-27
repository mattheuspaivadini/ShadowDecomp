/* KERNEL.XFF @ 0x005FE0 (108 B) - iosUsbSerialPrintf
 * Evidence: 256-byte stack buffer, vsprintf(buf, fmt, ap) (EE varargs save area), usbSerialSysPutString(buf).
 */
#include <stdarg.h>
int vsprintf(char *buf, const char *fmt, va_list ap);
void usbSerialSysPutString(const char *s);

void iosUsbSerialPrintf(const char *fmt, ...) {
    char buf[256];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    usbSerialSysPutString(buf);
}
