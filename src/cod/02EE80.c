/* asm/cod/02EE80.s -> pow5mult.
 * Newlib 1.9.0 mprec.c pow5mult (authentic source); Bfree/multadd/i2b/mult as NOTHROW_STUB (defined earlier in mprec.c) give the plain bnez delay fill (Session 28).
 * MATCHED. */
#include "nothrow_stub.h"
#include "newlib19_mprec.h"

/* mprec.c defines Bfree/multadd/i2b/mult before pow5mult (see nothrow_stub.h). */
void NOTHROW_STUB Bfree (struct _reent *p, _Bigint *v) {}
_Bigint * NOTHROW_STUB multadd (struct _reent *p, _Bigint *b, int m, int a) { return 0; }
_Bigint * NOTHROW_STUB i2b (struct _reent *p, int i) { return 0; }
_Bigint * NOTHROW_STUB mult (struct _reent *p, _Bigint *a, _Bigint *b) { return 0; }

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
