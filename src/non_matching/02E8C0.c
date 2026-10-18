/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 1 [cc=296] (was 24).
 * Authentic Newlib 1.9.0 mprec.c multadd (include/newlib19_mprec.h). Residual = bnez (original) vs bnel on the wds >= maxwds test (dbr annul class, same as 028850).
 * The original .s stays in the build (asm/cod/02E8C0.s); this C
 * draft (Session 23) is kept for the record. */
#include "newlib19_mprec.h"

_Bigint *
multadd (struct _reent *ptr, _Bigint * b, int m, int a)
{
  int i, wds;
  __ULong *x, y;
#ifdef Pack_32
  __ULong xi, z;
#endif
  _Bigint *b1;

  wds = b->_wds;
  x = b->_x;
  i = 0;
  do
    {
#ifdef Pack_32
      xi = *x;
      y = (xi & 0xffff) * m + a;
      z = (xi >> 16) * m + (y >> 16);
      a = (int) (z >> 16);
      *x++ = (z << 16) + (y & 0xffff);
#else
      y = *x * m + a;
      a = (int) (y >> 16);
      *x++ = y & 0xffff;
#endif
    }
  while (++i < wds);
  if (a)
    {
      if (wds >= b->_maxwds)
	{
	  b1 = Balloc (ptr, b->_k + 1);
	  Bcopy (b1, b);
	  Bfree (ptr, b);
	  b = b1;
	}
      b->_x[wds++] = a;
      b->_wds = wds;
    }
  return b;
}
