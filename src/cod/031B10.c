/* asm/cod/031B10.s -> float_to_si.
 * gcc-2.95.3 fp-bit.c L_df_to_si (authentic source, US_SOFTWARE_GOFAST)
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define L_df_to_si
#include "fp-bit.h"
#include "fp-bit-common.h"

SItype
float_to_si (FLO_type arg_a)
{
  fp_number_type a;
  SItype tmp;

  unpack_d ((FLO_union_type *) & arg_a, &a);
  if (iszero (&a))
    return 0;
  if (isnan (&a))
    return 0;
  /* get reasonable MAX_SI_INT... */
  if (isinf (&a))
    return a.sign ? (-MAX_SI_INT)-1 : MAX_SI_INT;
  /* it is a number, but a small one */
  if (a.normal_exp < 0)
    return 0;
  if (a.normal_exp > 30)
    return a.sign ? (-MAX_SI_INT)-1 : MAX_SI_INT;
  tmp = a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
  return a.sign ? (-tmp) : (tmp);
}
