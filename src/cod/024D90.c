/* asm/cod/024D90.s -> WORD_SIZE.
 * GCC 2.95.3 libgcc2.c L_fixunssfdi (authentic source, include/libgcc2.h + longlong.h)
 * MATCHED. */
#include "libgcc2.h"

#define WORD_SIZE (sizeof (SItype) * BITS_PER_UNIT)
#define HIGH_WORD_COEFF (((UDItype) 1) << WORD_SIZE)

DItype
__fixunssfdi (SFtype original_a)
{
  /* Convert the SFtype to a DFtype, because that is surely not going
     to lose any bits.  Some day someone else can write a faster version
     that avoids converting to DFtype, and verify it really works right.  */
  DFtype a = original_a;
  DFtype b;
  UDItype v;

  if (a < 0)
    return 0;

  /* Compute high word of result, as a flonum.  */
  b = (a / HIGH_WORD_COEFF);
  /* Convert that to fixed (but not to DItype!),
     and shift it into the high word.  */
  v = (USItype) b;
  v <<= WORD_SIZE;
  /* Remove high part from the DFtype, leaving the low part as flonum.  */
  a -= (DFtype)v;
  /* Convert that to fixed (but not to DItype!) and add it in.
     Sometimes A comes out negative.  This is significant, since
     A has more bits than a long int does.  */
  if (a < 0)
    v -= (USItype) (- a);
  else
    v += (USItype) a;
  return v;
}
