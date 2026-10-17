/* asm/cod/02C048.s -> vfprintf.
 * Newlib 1.9.0 stdio/vsprintf.c vsprintf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647
extern int func_00129930 (FILE *, const char *, va_list);	/* vfprintf (029930) */
#define vfprintf func_00129930
#define vsprintf func_0012C048

int
vsprintf (char *str, char const *fmt, va_list ap)
{
  int ret;
  FILE f;

  f._flags = __SWR | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._w = INT_MAX;
  f._data = _REENT;
  ret = vfprintf (&f, fmt, ap);
  *f._p = 0;
  return ret;
}
