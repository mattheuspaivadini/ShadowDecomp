/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 1 [cc=296] (was 27).
 * Rewritten from the SCE fp-bit pack_d template (FLOAT): zero test only, normal_exp > EXPBIAS+1 -> inf, and normal_exp == EXPBIAS+1 with the top fraction bit -> inf. Residual = beql (original) vs beqz on the > EXPBIAS+1 test (dbr annul class).
 * The original .s stays in the build (asm/cod/027390.s); this C
 * draft (Session 23) is kept for the record. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define FLOAT_BIT_ORDER_MISMATCH
#define FLOAT
#define L_pack_sf
#include "fp-bit.h"
#include "fp-bit-common.h"

FLO_type
__pack_f (fp_number_type *src)
{
  FLO_union_type dst;
  fractype fraction = src->fraction.ll;
  int sign = src->sign;
  int exp = 0;

  if (iszero (src))
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
      else if (src->normal_exp > EXPBIAS + 1)
	{
	  exp = EXPMAX;
	  fraction = 0;
	}
      else
	{
	  exp = src->normal_exp + EXPBIAS;
	  if (src->normal_exp == EXPBIAS + 1 && (fraction & 0x80000000))
	    {
	      exp = EXPMAX;
	      fraction = 0;
	    }
	  else
	    fraction >>= NGARDS;
	}
    }

  dst.bits.fraction = fraction;
  dst.bits.exp = exp;
  dst.bits.sign = sign;
  return dst.value;
}
