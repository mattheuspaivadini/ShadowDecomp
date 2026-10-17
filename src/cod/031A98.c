/* asm/cod/031A98.s -> __fixdfdi.
 * GCC 2.95.3 libgcc2.c L_fixdfdi (authentic source, include/libgcc2.h + longlong.h)
 * MATCHED. */
#include "libgcc2.h"

extern DItype __fixunsdfdi (DFtype a);

DItype
__fixdfdi (DFtype a)
{
  if (a < 0)
    return - __fixunsdfdi (-a);
  return __fixunsdfdi (a);
}
