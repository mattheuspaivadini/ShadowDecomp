/* asm/cod/02F790.s -> _mprec_log10.
 * Newlib 1.9.0 stdlib/mprec.c _mprec_log10 (authentic source, include/newlib19_mprec.h)
 * MATCHED. */
#include "newlib19_mprec.h"

double
_mprec_log10 (int dig)
{
  double v = 1.0;
  if (dig < 24)
    return tens[dig];
  while (dig > 0)
    {
      v *= 10;
      dig--;
    }
  return v;
}
