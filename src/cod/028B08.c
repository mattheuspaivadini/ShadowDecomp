/* asm/cod/028B08.s -> eofread.
 * Newlib 1.9.0 stdio/sscanf.c sscanf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

#define INT_MAX 2147483647

extern int __svfscanf (FILE *, const char *, va_list);
extern size_t func_001290C4 (const char *);	/* strlen (0290C4) */
#define strlen func_001290C4
extern int func_00128B00 (void *, char *, int);	/* sscanf.c static eofread (028B00) */
#define eofread func_00128B00

int
sscanf (const char *str, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;

  f._flags = __SRD;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._r = strlen (str);
  f._read = eofread;
  f._ub._base = NULL;
  f._lb._base = NULL;
  f._data = _REENT;
  va_start (ap, fmt);
  ret = __svfscanf (&f, fmt, ap);
  va_end (ap);
  return ret;
}
