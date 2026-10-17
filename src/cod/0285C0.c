/* asm/cod/0285C0.s -> vfprintf.
 * Newlib 1.9.0 stdio/printf.c printf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647
extern int func_00129930 (FILE *, const char *, va_list);	/* vfprintf (029930) */
#define vfprintf func_00129930
#define printf func_001285C0

int
printf (const char *fmt, ...)
{
  int ret;
  va_list ap;

  va_start (ap, fmt);
  _stdout_r (_REENT)->_data = _REENT;
  ret = vfprintf (_stdout_r (_REENT), fmt, ap);
  va_end (ap);
  return ret;
}
