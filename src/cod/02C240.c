/* asm/cod/02C240.s -> Sign_Extend.
 * Newlib 1.9.0 stdlib/dtoa.c static quorem (authentic source)
 * MATCHED. */
#include "newlib19_mprec.h"

#define Sign_Extend(a,b) /*no-op*/
#define quorem func_0012C240

int
quorem (_Bigint * b, _Bigint * S)
{
  int n;
  __Long borrow, y;
  __ULong carry, q, ys;
  __ULong *bx, *bxe, *sx, *sxe;
#ifdef Pack_32
  __Long z;
  __ULong si, zs;
#endif

  n = S->_wds;
#ifdef DEBUG
  /*debug*/ if (b->_wds > n)
    /*debug*/ Bug ("oversize b in quorem");
#endif
  if (b->_wds < n)
    return 0;
  sx = S->_x;
  sxe = sx + --n;
  bx = b->_x;
  bxe = bx + n;
  q = *bxe / (*sxe + 1);	/* ensure q <= true quotient */
#ifdef DEBUG
  /*debug*/ if (q > 9)
    /*debug*/ Bug ("oversized quotient in quorem");
#endif
  if (q)
    {
      borrow = 0;
      carry = 0;
      do
	{
#ifdef Pack_32
	  si = *sx++;
	  ys = (si & 0xffff) * q + carry;
	  zs = (si >> 16) * q + (ys >> 16);
	  carry = zs >> 16;
	  y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  z = (*bx >> 16) - (zs & 0xffff) + borrow;
	  borrow = z >> 16;
	  Sign_Extend (borrow, z);
	  Storeinc (bx, z, y);
#else
	  ys = *sx++ * q + carry;
	  carry = ys >> 16;
	  y = *bx - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  *bx++ = y & 0xffff;
#endif
	}
      while (sx <= sxe);
      if (!*bxe)
	{
	  bx = b->_x;
	  while (--bxe > bx && !*bxe)
	    --n;
	  b->_wds = n;
	}
    }
  if (cmp (b, S) >= 0)
    {
      q++;
      borrow = 0;
      carry = 0;
      bx = b->_x;
      sx = S->_x;
      do
	{
#ifdef Pack_32
	  si = *sx++;
	  ys = (si & 0xffff) + carry;
	  zs = (si >> 16) + (ys >> 16);
	  carry = zs >> 16;
	  y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  z = (*bx >> 16) - (zs & 0xffff) + borrow;
	  borrow = z >> 16;
	  Sign_Extend (borrow, z);
	  Storeinc (bx, z, y);
#else
	  ys = *sx++ + carry;
	  carry = ys >> 16;
	  y = *bx - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  *bx++ = y & 0xffff;
#endif
	}
      while (sx <= sxe);
      bx = b->_x;
      bxe = bx + n;
      if (!*bxe)
	{
	  while (--bxe > bx && !*bxe)
	    --n;
	  b->_wds = n;
	}
    }
  return q;
}
