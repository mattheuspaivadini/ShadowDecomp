/* asm/cod/027390.s -> __pack_f.
 * fp-bit pack_f (FLOAT); exp kept live at the normal-range entry by an asm use (beql slot) (Session 42)
 * MATCHED. */
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
	  asm volatile("" : : "r"(exp));	/* exp live here: reorg annuls the > EXPBIAS+1 slot (beql) */
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
