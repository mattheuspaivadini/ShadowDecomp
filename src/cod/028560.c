/* asm/cod/028560.s -> _printf_r.
 * Newlib 1.9.0 stdio/printf.c _printf_r (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647

extern int _vfprintf_r (struct _reent *, FILE *, const char *, va_list);

int
_printf_r (struct _reent *ptr, const char *fmt, ...)
{
  int ret;
  va_list ap;

  va_start (ap, fmt);
  ret = _vfprintf_r (ptr, _stdout_r (ptr), fmt, ap);
  va_end (ap);
  return ret;
}
