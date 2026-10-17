/* asm/cod/026FA0.s -> WORD_SIZE.
 * GCC 2.95.3 libgcc2.c L_floatdidf (authentic source, include/libgcc2.h + longlong.h)
 * MATCHED. */
#include "libgcc2.h"

#define WORD_SIZE (sizeof (SItype) * BITS_PER_UNIT)
#define HIGH_HALFWORD_COEFF (((UDItype) 1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype) 1) << WORD_SIZE)

DFtype
__floatdidf (DItype u)
{
  DFtype d;

  d = (SItype) (u >> WORD_SIZE);
  d *= HIGH_HALFWORD_COEFF;
  d *= HIGH_HALFWORD_COEFF;
  d += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return d;
}
