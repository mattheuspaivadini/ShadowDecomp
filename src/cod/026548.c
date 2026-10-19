/* asm/cod/026548.s -> find_fde.
 * GCC 2000-06 frame-dwarf2.c find_fde (authentic source, include/frame2000.h); frame_init/search_fdes as NOTHROW_STUB so their calls are nothrow like in the original TU, which turns the annulled bnel into the original plain bne (Session 28).
 * MATCHED. */
#include "frame2000.h"
#include "nothrow_stub.h"

/* frame.c defines these before find_fde (see nothrow_stub.h). */
void NOTHROW_STUB frame_init (struct object *ob) {}
fde * NOTHROW_STUB search_fdes (fde *this_fde, void *pc) { return 0; }

fde *
find_fde (void *pc)
{
  struct object *ob;
  size_t lo, hi;

  init_object_mutex_once ();
  __gthread_mutex_lock (&object_mutex);

  /* Linear search through the objects, to find the one containing the pc. */
  for (ob = objects; ob; ob = ob->next)
    {
      if (ob->pc_begin == 0)
	frame_init (ob);
      if (pc >= ob->pc_begin && pc < ob->pc_end)
	break;
    }

  if (ob == 0)
    {
      __gthread_mutex_unlock (&object_mutex);
      return 0;
    }

  if (!ob->fde_array || (void *)ob->fde_array == (void *)ob->fde_begin)
    frame_init (ob);

  if (ob->fde_array && (void *)ob->fde_array != (void *)ob->fde_begin)
    {
      __gthread_mutex_unlock (&object_mutex);
      
      /* Standard binary search algorithm.  */
      for (lo = 0, hi = ob->count; lo < hi; )
	{
	  size_t i = (lo + hi) / 2;
	  fde *f = ob->fde_array[i];

	  if (pc < f->pc_begin)
	    hi = i;
	  else if (pc >= f->pc_begin + f->pc_range)
	    lo = i + 1;
	  else
	    return f;
	}
    }
  else
    {
      /* Long slow labourious linear search, cos we've no memory. */
      fde *f;
      
      if (ob->fde_array)
	{
	  fde **p = ob->fde_array;
	  
	  do
	    {
	      f = search_fdes (*p, pc);
	      if (f)
		break;
	      p++;
	    }
	  while (*p);
	}
      else
	f = search_fdes (ob->fde_begin, pc);
      __gthread_mutex_unlock (&object_mutex);
      return f;
    }
  return 0;
}
