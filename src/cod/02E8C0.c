/* asm/cod/02E8C0.s -> multadd.
 * Newlib 1.9.0 mprec.c multadd (authentic source); Balloc/Bfree as NOTHROW_STUB (defined earlier in mprec.c) give the plain bnez delay fill (Session 28).
 * MATCHED. */
#include "nothrow_stub.h"
#include "newlib19_mprec.h"

/* mprec.c defines Balloc/Bfree before multadd (see nothrow_stub.h). */
_Bigint * NOTHROW_STUB Balloc (struct _reent *p, int k) { return 0; }
void NOTHROW_STUB Bfree (struct _reent *p, _Bigint *v) {}

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
