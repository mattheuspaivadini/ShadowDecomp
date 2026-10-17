/* asm/cod/029930.s -> VFPRINTF.
 * Newlib 1.9.0 stdio/vfprintf.c vfprintf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647

extern int _vfprintf_r (struct _reent *, FILE *, const char *, va_list);
#define VFPRINTF func_00129930	/* vfprintf */
#define _VFPRINTF_R _vfprintf_r

int
VFPRINTF (FILE * fp, const char *fmt0, va_list ap)
{
  CHECK_INIT (fp);
  return _VFPRINTF_R (fp->_data, fp, fmt0, ap);
}
