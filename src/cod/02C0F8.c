/* asm/cod/02C0F8.s -> __swsetup.
 * Newlib 1.9.0 stdio/wsetup.c __swsetup (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

int
__swsetup (register FILE * fp)
{
  /* Make sure stdio is set up.  */

  CHECK_INIT (fp);

  /*
   * If we are not writing, we had better be reading and writing.
   */

  if ((fp->_flags & __SWR) == 0)
    {
      if ((fp->_flags & __SRW) == 0)
	return EOF;
      if (fp->_flags & __SRD)
	{
	  /* clobber any ungetc data */
	  if (HASUB (fp))
	    FREEUB (fp);
	  fp->_flags &= ~(__SRD | __SEOF);
	  fp->_r = 0;
	  fp->_p = fp->_bf._base;
	}
      fp->_flags |= __SWR;
    }

  /*
   * Make a buffer if necessary, then set _w.
   */
  /* NOT NEEDED FOR CYGNUS SPRINTF ONLY jpg */
  if (fp->_bf._base == NULL)
    __smakebuf (fp);

  if (fp->_flags & __SLBF)
    {
      /*
       * It is line buffered, so make _lbfsize be -_bufsize
       * for the putc() macro.  We will change _lbfsize back
       * to 0 whenever we turn off __SWR.
       */
      fp->_w = 0;
      fp->_lbfsize = -fp->_bf._size;
    }
  else
    fp->_w = fp->_flags & __SNBF ? 0 : fp->_bf._size;

  return 0;
}
