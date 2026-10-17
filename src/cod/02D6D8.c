/* asm/cod/02D6D8.s -> or.
 * Newlib 1.9.0 stdio/fflush.c fflush (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

/* Flush a single file, or (if fp is NULL) all files.  */

int
fflush (register FILE * fp)
{
  register unsigned char *p;
  register int n, t;

  if (fp == NULL)
    return _fwalk (_REENT, fflush);

  CHECK_INIT (fp);

  t = fp->_flags;
  if ((t & __SWR) == 0 || (p = fp->_bf._base) == NULL)
    return 0;
  n = fp->_p - p;		/* write this much */

  /*
   * Set these immediately to avoid problems with longjmp
   * and to allow exchange buffering (via setvbuf) in user
   * write function.
   */
  fp->_p = p;
  fp->_w = t & (__SLBF | __SNBF) ? 0 : fp->_bf._size;

  while (n > 0)
    {
      t = (*fp->_write) (fp->_cookie, (char *) p, n);
      if (t <= 0)
	{
	  fp->_flags |= __SERR;
	  return EOF;
	}
      p += t;
      n -= t;
    }
  return 0;
}
