/* asm/cod/02D850.s -> __sfmoreglue.
 * Newlib 1.9.0 stdio/findfp.c __sfmoreglue (authentic source, include/newlib19.h)
 * MATCHED. */
#include "newlib19.h"

struct _glue *
__sfmoreglue (struct _reent *d, register int n)
{
  struct _glue *g;
  FILE *p;

  g = (struct _glue *) _malloc_r (d, sizeof (*g) + n * sizeof (FILE));
  if (g == NULL)
    return NULL;
  p = (FILE *) (g + 1);
  g->_next = NULL;
  g->_niobs = n;
  g->_iobs = p;
  func_001283D0 (p, 0, n * sizeof (FILE));
  return g;
}
