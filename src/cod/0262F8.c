/* asm/cod/0262F8.s -> add_fdes.
 * GCC frame.c/frame-dwarf2.c add_fdes (authentic source)
 * MATCHED. */
#include "frame2000.h"

void
add_fdes (fde *this_fde, fde_accumulator *accu, void **beg_ptr, void **end_ptr)
{
  void *pc_begin = *beg_ptr;
  void *pc_end = *end_ptr;

  for (; this_fde->length != 0; this_fde = next_fde (this_fde))
    {
      /* Skip CIEs and linked once FDE entries.  */
      if (this_fde->CIE_delta == 0 || this_fde->pc_begin == 0)
	continue;

      fde_insert (accu, this_fde);

      if (this_fde->pc_begin < pc_begin)
	pc_begin = this_fde->pc_begin;
      if (this_fde->pc_begin + this_fde->pc_range > pc_end)
	pc_end = this_fde->pc_begin + this_fde->pc_range;
    }

  *beg_ptr = pc_begin;
  *end_ptr = pc_end;
}
