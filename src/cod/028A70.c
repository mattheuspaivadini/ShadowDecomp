/* asm/cod/028A70.s -> vfprintf.
 * Newlib 1.9.0 stdio/sprintf.c sprintf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647
extern int func_00129930 (FILE *, const char *, va_list);	/* vfprintf (029930) */
#define vfprintf func_00129930
#define sprintf func_00128A70

int
sprintf (char *str, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;

  f._flags = __SWR | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._w = INT_MAX;
  f._data = _REENT;
  va_start (ap, fmt);
  ret = vfprintf (&f, fmt, ap);
  va_end (ap);
  *f._p = 0;
  return (ret);
}
