/* asm/cod/026388.s -> search_fdes.
 * GCC frame.c/frame-dwarf2.c search_fdes (authentic source)
 * MATCHED. */
#include "frame2000.h"

fde *
search_fdes (fde *this_fde, void *pc)
{
  for (; this_fde->length != 0; this_fde = next_fde (this_fde))
    {
      /* Skip CIEs and linked once FDE entries.  */
      if (this_fde->CIE_delta == 0 || this_fde->pc_begin == 0)
	continue;

      if ((uaddr)((char *)pc - (char *)this_fde->pc_begin) < this_fde->pc_range)
	return this_fde;
    }
  return NULL;
}
