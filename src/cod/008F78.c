/* asm/cod/008F78.s -> kprintf.
 * SCE kprintf; scePrintf twin with the kernel tty callback (Session 19)
 * MATCHED. */
#include "stdarg.h"

int  DIntr(void);
int  EIntr(void);
int  func_00107FF8(int (*cb)(), int *p, unsigned int a1, const char *fmt, va_list ap);
int  func_00108D90(int a, int b, int c);

void kprintf(const char *fmt, ...) {
    va_list ap;
    int buf;
    int g;

    buf = 0;
    g = DIntr();
    va_start(ap, fmt);
    func_00107FF8(func_00108D90, &buf, 0xFFFFFFFF, fmt, ap);
    va_end(ap);
    if (g != 0)
        EIntr();
}
