/* asm/cod/031048.s -> if.
 * Newlib 1.9.0 stdlib/mallocr.c _calloc_r (cALLOc) (authentic source, include/newlib19_malloc.h)
 * MATCHED. */
#include "newlib19_malloc.h"

#if __STD_C
Void_t* cALLOc(RARG size_t n, size_t elem_size)
#else
Void_t* cALLOc(RARG n, elem_size) RDECL size_t n; size_t elem_size;
#endif
{
  mchunkptr p;
  INTERNAL_SIZE_T csz;

  INTERNAL_SIZE_T sz = n * elem_size;

#if MORECORE_CLEARS
  mchunkptr oldtop;
  INTERNAL_SIZE_T oldtopsize;
#endif
  Void_t* mem;

  /* check if expand_top called, in which case don't need to clear */
#if MORECORE_CLEARS
  MALLOC_LOCK;
  oldtop = top;
  oldtopsize = chunksize(top);
#endif

  mem = mALLOc (RCALL sz);

  if (mem == 0) 
  {
#if MORECORE_CLEARS
    MALLOC_UNLOCK;
#endif
    return 0;
  }
  else
  {
    p = mem2chunk(mem);

    /* Two optional cases in which clearing not necessary */


#if HAVE_MMAP
    if (chunk_is_mmapped(p))
    {
#if MORECORE_CLEARS
      MALLOC_UNLOCK;
#endif
      return mem;
    }
#endif

    csz = chunksize(p);

#if MORECORE_CLEARS
    if (p == oldtop && csz > oldtopsize) 
    {
      /* clear only the bytes from non-freshly-sbrked memory */
      csz = oldtopsize;
    }
    MALLOC_UNLOCK;
#endif

    MALLOC_ZERO(mem, csz - SIZE_SZ);
    return mem;
  }
}
