/* asm/cod/025B30.s -> external.
 * GCC 2000-06 frame.c end_fde_sort (authentic source, include/frame2000.h); fde_merge as NOTHROW_STUB (defined earlier in frame.c), free stays external - stubbing free breaks the match (Session 28).
 * MATCHED. */
#include "nothrow_stub.h"
#include "frame2000.h"

/* frame.c defines fde_merge before end_fde_sort; free stays external (see nothrow_stub.h). */
void NOTHROW_STUB fde_merge (fde_vector *v1, const fde_vector *v2) {}

fde **
end_fde_sort (fde_accumulator *accu, size_t count)
{
  if (accu->linear.array && accu->linear.count != count)
    abort ();
  
  if (accu->erratic.array)
    {
      fde_split (&accu->linear, &accu->erratic);
      if (accu->linear.count + accu->erratic.count != count)
	abort ();
      frame_heapsort (&accu->erratic);
      fde_merge (&accu->linear, &accu->erratic);
      free (accu->erratic.array);
    }
  else
    {
      /* We've not managed to malloc an erratic array, so heap sort in the
         linear one.  */
      frame_heapsort (&accu->linear);
    }
  return accu->linear.array;
}
