/* asm/cod/027048.s -> unpack_d.
 * gcc fp-bit.c (SCE EE variant: no denormals/rounding, Session 19)
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define FLOAT
#define L_unpack_sf
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
  else
    {
      dst->normal_exp = exp - EXPBIAS;
      dst->class = CLASS_NUMBER;
      dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}
