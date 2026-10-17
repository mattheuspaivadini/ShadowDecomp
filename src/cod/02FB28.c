/* asm/cod/02FB28.s -> __sseek.
 * Newlib 1.9.0 stdio/stdio.c __sseek (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

fpos_t
__sseek (void *cookie, fpos_t offset, int whence)
{
  register FILE *fp = (FILE *) cookie;
  register off_t ret;

  ret = _lseek_r (fp->_data, fp->_file, (off_t) offset, whence);
  if (ret == -1L)
    fp->_flags &= ~__SOFF;
  else
    {
      fp->_flags |= __SOFF;
      fp->_offset = ret;
    }
  return ret;
}
