/* asm/cod/02FAA8.s -> __swrite.
 * Newlib 1.9.0 stdio/stdio.c __swrite (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

int
__swrite (void *cookie, char const *buf, int n)
{
  register FILE *fp = (FILE *) cookie;
  int w;

  if (fp->_flags & __SAPP)
    (void) _lseek_r (fp->_data, fp->_file, (off_t) 0, SEEK_END);
  fp->_flags &= ~__SOFF;	/* in case O_APPEND mode is set */

  w = _write_r (fp->_data, fp->_file, buf, n);

  return w;
}
