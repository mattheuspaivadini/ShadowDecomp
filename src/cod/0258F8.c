/* asm/cod/0258F8.s -> float_to_usi.
 * gcc-2.95.3 fp-bit.c L_df_to_usi (authentic source, US_SOFTWARE_GOFAST)
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define L_df_to_usi
#include "fp-bit.h"
#include "fp-bit-common.h"

#ifdef US_SOFTWARE_GOFAST
/* While libgcc2.c defines its own __fixunssfsi and __fixunsdfsi routines,
   we also define them for GOFAST because the ones in libgcc2.c have the
   wrong names and I'd rather define these here and keep GOFAST CYG-LOC's
   out of libgcc2.c.  We can't define these here if not GOFAST because then
   there'd be duplicate copies.  */

USItype
float_to_usi (FLO_type arg_a)
{
  fp_number_type a;

  unpack_d ((FLO_union_type *) & arg_a, &a);
  if (iszero (&a))
    return 0;
  if (isnan (&a))
    return 0;
  /* it is a negative number */
  if (a.sign)
    return 0;
  /* get reasonable MAX_USI_INT... */
  if (isinf (&a))
    return MAX_USI_INT;
  /* it is a number, but a small one */
  if (a.normal_exp < 0)
    return 0;
  if (a.normal_exp > 31)
    return MAX_USI_INT;
  else if (a.normal_exp > (FRACBITS + NGARDS))
    return a.fraction.ll << (a.normal_exp - (FRACBITS + NGARDS));
  else
    return a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
}
#endif
