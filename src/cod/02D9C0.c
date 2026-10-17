/* asm/cod/02D9C0.s -> _cleanup_r.
 * Newlib 1.9.0 stdio/findfp.c _cleanup_r (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

void
_cleanup_r (struct _reent *ptr)
{
  /* (void) _fwalk(fclose); */
  (void) _fwalk (ptr, fflush);	/* cheating */
}
