/* asm/cod/008DB8.s -> func_00108DB8.
 * func_00108DB8 (matching, cc=29)
 * MATCHED. */
#include <stdarg.h>

extern int func_00107FF8(int (*cb)(), int a1, int a2, int a3, va_list ap);

int func_00108DB8(int (*cb)(), int a1, int *a2, int a3, ...) {
    va_list ap;
    int r;

    va_start(ap, a3);
    r = func_00107FF8(cb, a1, *a2, a3, ap);
    va_end(ap);
    *a2 = *a2 - r;
    return r;
}
