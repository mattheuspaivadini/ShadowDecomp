/* asm/cod/02D8C8.s -> __sfp.
 * Newlib 1.9.0 stdio/findfp.c __sfp (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

#define ENOMEM 12

FILE *
__sfp (struct _reent *d)
{
  FILE *fp;
  int n;
  struct _glue *g;

  if (!d->__sdidinit)
    __sinit (d);
  for (g = &d->__sglue;; g = g->_next)
    {
      for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
	if (fp->_flags == 0)
	  goto found;
      if (g->_next == NULL &&
	  (g->_next = __sfmoreglue (d, NDYNAMIC)) == NULL)
	break;
    }
  d->_errno = ENOMEM;
  return NULL;

found:
  fp->_flags = 1;		/* reserve this slot; caller sets real flags */
  fp->_p = NULL;		/* no current pointer */
  fp->_w = 0;			/* nothing to read or write */
  fp->_r = 0;
  fp->_bf._base = NULL;		/* no buffer */
  fp->_bf._size = 0;
  fp->_lbfsize = 0;		/* not line buffered */
  fp->_file = -1;		/* no file */
  /* fp->_cookie = <any>; */	/* caller sets cookie, _read/_write etc */
  fp->_ub._base = NULL;		/* no ungetc buffer */
  fp->_ub._size = 0;
  fp->_lb._base = NULL;		/* no line buffer */
  fp->_lb._size = 0;
  fp->_data = d;
  return fp;
}
