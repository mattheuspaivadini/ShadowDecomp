/* asm/cod/002CF8.s -> LoaderSysPrintf.
 * loader printf: va_list into vsprintf, then printf (Session 19)
 * MATCHED. */
#include "stdarg.h"

int  func_0012C048(char *buf, const char *fmt, va_list ap);   /* vsprintf */
void func_001285C0(char *s);
int  func_001290C4(const char *s);                             /* strlen */

void LoaderSysPrintf(const char *fmt, ...) {
    char buf[0x100];
    va_list ap;

    va_start(ap, fmt);
    func_0012C048(buf, fmt, ap);
    va_end(ap);
    func_001285C0(buf);
    func_001290C4(buf);
}
