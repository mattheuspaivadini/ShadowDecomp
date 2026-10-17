/* asm/cod/0270D8.s -> pack_d.
 * gcc fp-bit.c (SCE EE variant: no denormals/rounding, Session 19)
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define FLOAT_BIT_ORDER_MISMATCH
#define L_pack_df
#include "fp-bit.h"
#include "fp-bit-common.h"

FLO_type
pack_d ( fp_number_type *  src)
{
  FLO_union_type dst;
  fractype fraction = src->fraction.ll;	/* wasn't unsigned before? */
  int sign = src->sign;
  int exp = 0;

  if (isnan (src))
    {
      exp = EXPMAX;
      if (src->class == CLASS_QNAN || 1)
	{
	  fraction |= QUIET_NAN;
	}
    }
  else if (isinf (src))
    {
      exp = EXPMAX;
      fraction = 0;
    }
  else if (iszero (src))
    {
      exp = 0;
      fraction = 0;
    }
  else if (fraction == 0)
    {
      exp = 0;
    }
  else
    {
      if (src->normal_exp < NORMAL_EXPMIN)
	{
	  exp = 0;
	  fraction = 0;
	}
      else if (src->normal_exp > EXPBIAS)
	{
	  exp = EXPMAX;
	  fraction = 0;
	}
      else
	{
	  exp = src->normal_exp + EXPBIAS;
	  fraction >>= NGARDS;
	}
    }

  dst.bits.fraction = fraction;
  dst.bits.exp = exp;
  dst.bits.sign = sign;
  return dst.value;
}
