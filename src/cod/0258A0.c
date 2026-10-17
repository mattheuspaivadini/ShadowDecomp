/* asm/cod/0258A0.s -> df_to_sf.
 * gcc-3.0 fp-bit.c L_df_to_sf (authentic source, US_SOFTWARE_GOFAST), Session 19
 * MATCHED. */
#define FINE_GRAINED_LIBRARIES
#define US_SOFTWARE_GOFAST
#define L_df_to_sf
#include "fp-bit.h"
#include "fp-bit-common.h"

SFtype
df_to_sf (DFtype arg_a)
{
  fp_number_type in;
  USItype sffrac;
  FLO_union_type au;

  au.value = arg_a;
  unpack_d (&au, &in);

  sffrac = in.fraction.ll >> F_D_BITOFF;

  /* We set the lowest guard bit in SFFRAC if we discarded any non
     zero bits.  */
  if ((in.fraction.ll & (((USItype) 1 << F_D_BITOFF) - 1)) != 0)
    sffrac |= 1;

  return __make_fp (in.class, in.sign, in.normal_exp, sffrac);
}
