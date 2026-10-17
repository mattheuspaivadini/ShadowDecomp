/* asm/cod/0271B0.s -> unpack_d.
 * gcc fp-bit.c (SCE EE variant: no denormals/rounding, Session 19)
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define L_unpack_df
#include "fp-bit.h"
#include "fp-bit-common.h"

void
unpack_d (FLO_union_type * src, fp_number_type * dst)
{
  fractype fraction;
  int exp;
  int sign;

  fraction = src->value_raw & ((((fractype)1) << FRACBITS) - (fractype)1);
  exp = ((int)(src->value_raw >> FRACBITS)) & ((1 << EXPBITS) - 1);
  sign = ((int)(src->value_raw >> (FRACBITS + EXPBITS))) & 1;

  dst->sign = sign;
  if (exp == 0)
    {
      dst->class = CLASS_ZERO;
    }
  else if (exp == EXPMAX)
    {
      dst->normal_exp = EXPBIAS;
      if (fraction == 0)
	{
	  dst->class = CLASS_INFINITY;
	  dst->fraction.ll = IMPLICIT_1;
	}
      else
	{
	  if (fraction & QUIET_NAN)
	    {
	      dst->class = CLASS_QNAN;
	    }
	  else
	    {
	      dst->class = CLASS_SNAN;
	    }
	  dst->fraction.ll = fraction;
	}
    }
  else
    {
      dst->normal_exp = exp - EXPBIAS;
      dst->class = CLASS_NUMBER;
      dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}
