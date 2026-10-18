/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 1 [cc=296] (was 46).
 * Authentic Newlib 1.9.0 mprec.c pow5mult; p05 referenced through splat's D_00139B4C label (one word before the table). Residual = bnez (original) vs bnel after the _p5s load (dbr annul class; -g levels, -fno-thread-jumps and the 2.95/3.2 builds do not change it).
 * The original .s stays in the build (asm/cod/02EE80.s); this C
 * draft (Session 23) is kept for the record. */
#include "newlib19_mprec.h"

/* p05[3] = {5, 25, 125} sits at 0x00139B50; splat's label D_00139B4C is one
 * word before it, so p05[i - 1] is written D_00139B4C[i]. */
extern const int D_00139B4C[];

_Bigint *
pow5mult (struct _reent * ptr, _Bigint * b, int k)
{
  _Bigint *b1, *p5, *p51;
  int i;

  if ((i = k & 3) != 0)
    b = multadd (ptr, b, D_00139B4C[i], 0);

  if (!(k >>= 2))
    return b;
  if (!(p5 = ptr->_p5s))
    {
      /* first time */
      p5 = ptr->_p5s = i2b (ptr, 625);
      p5->_next = 0;
    }
  for (;;)
    {
      if (k & 1)
	{
	  b1 = mult (ptr, b, p5);
	  Bfree (ptr, b);
	  b = b1;
	}
      if (!(k >>= 1))
	break;
      if (!(p51 = p5->_next))
	{
	  p51 = p5->_next = mult (ptr, p5, p5);
	  p51->_next = 0;
	}
      p5 = p51;
    }
  return b;
}
