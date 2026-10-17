/* asm/cod/0263E0.s -> frame_init.
 * GCC frame.c/frame-dwarf2.c frame_init (authentic source)
 * MATCHED. */
#include "frame2000.h"

void
frame_init (struct object* ob)
{
  size_t count;
  fde_accumulator accu;
  void *pc_begin, *pc_end;
  fde **array;

  if (ob->pc_begin)
    count = ob->count;
  else if (ob->fde_array)
    {
      fde **p = ob->fde_array;
      for (count = 0; *p; ++p)
	count += count_fdes (*p);
    }
  else
    count = count_fdes (ob->fde_begin);
  ob->count = count;

  if (!start_fde_sort (&accu, count) && ob->pc_begin)
    return;

  pc_begin = (void*)(uaddr)-1;
  pc_end = 0;

  if (ob->fde_array)
    {
      fde **p = ob->fde_array;
      for (; *p; ++p)
	add_fdes (*p, &accu, &pc_begin, &pc_end);
    }
  else
    add_fdes (ob->fde_begin, &accu, &pc_begin, &pc_end);

  array = end_fde_sort (&accu, count);
  if (array)
    ob->fde_array = array;
  ob->pc_begin = pc_begin;
  ob->pc_end = pc_end;
}
