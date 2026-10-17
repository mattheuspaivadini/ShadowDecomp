/* asm/cod/027808.s -> if.
 * Newlib 1.9.0 stdlib/mallocr.c malloc_extend_top (static) (authentic source, include/newlib19_malloc.h)
 * MATCHED. */
#include "newlib19_malloc.h"

#define malloc_extend_top func_00127808

#if __STD_C
void malloc_extend_top(RARG INTERNAL_SIZE_T nb)
#else
void malloc_extend_top(RARG nb) RDECL INTERNAL_SIZE_T nb;
#endif
{
  char*     brk;                  /* return value from sbrk */
  INTERNAL_SIZE_T front_misalign; /* unusable bytes at front of sbrked space */
  INTERNAL_SIZE_T correction;     /* bytes for 2nd sbrk call */
  char*     new_brk;              /* return of 2nd sbrk call */
  INTERNAL_SIZE_T top_size;       /* new size of top chunk */

  mchunkptr old_top     = top;  /* Record state of old top */
  INTERNAL_SIZE_T old_top_size = chunksize(old_top);
  char*     old_end      = (char*)(chunk_at_offset(old_top, old_top_size));

  /* Pad request with top_pad plus minimal overhead */
  
  INTERNAL_SIZE_T    sbrk_size     = nb + top_pad + MINSIZE;
  unsigned long pagesz    = malloc_getpagesize;

  /* If not the first time through, round to preserve page boundary */
  /* Otherwise, we need to correct to a page size below anyway. */
  /* (We also correct below if an intervening foreign sbrk call.) */

  if (sbrk_base != (char*)(-1))
    sbrk_size = (sbrk_size + (pagesz - 1)) & ~(pagesz - 1);

  brk = (char*)(MORECORE (sbrk_size));

  /* Fail if sbrk failed or if a foreign sbrk call killed our space */
  if (brk == (char*)(MORECORE_FAILURE) || 
      (brk < old_end && old_top != initial_top))
    return;     

  sbrked_mem += sbrk_size;

  if (brk == old_end) /* can just add bytes to current top */
  {
    top_size = sbrk_size + old_top_size;
    set_head(top, top_size | PREV_INUSE);
  }
  else
  {
    if (sbrk_base == (char*)(-1))  /* First time through. Record base */
      sbrk_base = brk;
    else  /* Someone else called sbrk().  Count those bytes as sbrked_mem. */
      sbrked_mem += brk - (char*)old_end;

    /* Guarantee alignment of first new chunk made from this space */
    front_misalign = (POINTER_UINT)chunk2mem(brk) & MALLOC_ALIGN_MASK;
    if (front_misalign > 0) 
    {
      correction = (MALLOC_ALIGNMENT) - front_misalign;
      brk += correction;
    }
    else
      correction = 0;

    /* Guarantee the next brk will be at a page boundary */
    correction += pagesz - ((POINTER_UINT)(brk + sbrk_size) & (pagesz - 1));

    /* Allocate correction */
    new_brk = (char*)(MORECORE (correction));
    if (new_brk == (char*)(MORECORE_FAILURE)) return; 

    sbrked_mem += correction;

    top = (mchunkptr)brk;
    top_size = new_brk - brk + correction;
    set_head(top, top_size | PREV_INUSE);

    if (old_top != initial_top)
    {

      /* There must have been an intervening foreign sbrk call. */
      /* A double fencepost is necessary to prevent consolidation */

      /* If not enough space to do this, then user did something very wrong */
      if (old_top_size < MINSIZE) 
      {
        set_head(top, PREV_INUSE); /* will force null return from malloc */
        return;
      }

      /* Also keep size a multiple of MALLOC_ALIGNMENT */
      old_top_size = (old_top_size - 3*SIZE_SZ) & ~MALLOC_ALIGN_MASK;
      set_head_size(old_top, old_top_size);
      chunk_at_offset(old_top, old_top_size          )->size =
        SIZE_SZ|PREV_INUSE;
      chunk_at_offset(old_top, old_top_size + SIZE_SZ)->size =
        SIZE_SZ|PREV_INUSE;
      /* If possible, release the rest. */
      if (old_top_size >= MINSIZE) 
        fREe(RCALL chunk2mem(old_top));
    }
  }

  if ((unsigned long)sbrked_mem > (unsigned long)max_sbrked_mem) 
    max_sbrked_mem = sbrked_mem;
#if HAVE_MMAP
  if ((unsigned long)(mmapped_mem + sbrked_mem) > (unsigned long)max_total_mem) 
    max_total_mem = mmapped_mem + sbrked_mem;
#else
  if ((unsigned long)(sbrked_mem) > (unsigned long)max_total_mem) 
    max_total_mem = sbrked_mem;
#endif

  /* We always land on a page boundary */
  assert(((unsigned long)((char*)top + top_size) & (pagesz - 1)) == 0);
}
