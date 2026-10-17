/* asm/cod/026F28.s -> __muldi3.
 * GCC 2.95.3 libgcc2.c L_muldi3 (authentic source, include/libgcc2.h + longlong.h)
 * MATCHED. */
#include "libgcc2.h"

DItype
__muldi3 (DItype u, DItype v)
{
  DIunion w;
  DIunion uu, vv;

  uu.ll = u,
  vv.ll = v;

  w.ll = __umulsidi3 (uu.s.low, vv.s.low);
  w.s.high += ((USItype) uu.s.low * (USItype) vv.s.high
	       + (USItype) uu.s.high * (USItype) vv.s.low);

  return w.ll;
}
