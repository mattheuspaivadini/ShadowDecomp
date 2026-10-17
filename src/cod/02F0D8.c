/* asm/cod/02F0D8.s -> cmp.
 * Newlib 1.9.0 stdlib/mprec.c cmp (authentic source, include/newlib19_mprec.h)
 * MATCHED. */
#include "newlib19_mprec.h"

int
cmp (_Bigint * a, _Bigint * b)
{
  __ULong *xa, *xa0, *xb, *xb0;
  int i, j;

  i = a->_wds;
  j = b->_wds;
  if (i -= j)
    return i;
  xa0 = a->_x;
  xa = xa0 + j;
  xb0 = b->_x;
  xb = xb0 + j;
  for (;;)
    {
      if (*--xa != *--xb)
	return *xa < *xb ? -1 : 1;
      if (xa <= xa0)
	break;
    }
  return 0;
}
