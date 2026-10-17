/* asm/cod/005268.s -> usbSerialSysPrintf.
 * usb serial printf: va_list into vsprintf (Session 19)
 * MATCHED. */
#include "stdarg.h"

int  func_0012C048(char *buf, const char *fmt, va_list ap);   /* vsprintf */
void usbSerialSysPutString(char *s);

void usbSerialSysPrintf(const char *fmt, ...) {
    char buf[0x100];
    va_list ap;

    va_start(ap, fmt);
    func_0012C048(buf, fmt, ap);
    va_end(ap);
    usbSerialSysPutString(buf);
}
