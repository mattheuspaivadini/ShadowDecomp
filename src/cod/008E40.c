/* asm/cod/008E40.s -> sceSnprintf.
 * sceSnprintf (matching, cc=29)
 * MATCHED. */
#include <stdarg.h>

extern int func_00108D10(void);
extern int func_00107FF8(int (*cb)(), int *p, int a1, int a2, va_list ap);

int sceSnprintf(int a0, int a1, int a2, ...) {
    int buf;
    va_list ap;
    int r;

    buf = a0;
    va_start(ap, a2);
    r = func_00107FF8(func_00108D10, &buf, a1, a2, ap);
    va_end(ap);
    return r;
}
