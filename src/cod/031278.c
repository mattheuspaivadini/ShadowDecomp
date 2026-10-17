/* asm/cod/031278.s -> if.
 * Newlib 1.9.0 stdlib/mallocr.c _realloc_r (rEALLOc) (authentic source, include/newlib19_malloc.h)
 * MATCHED. */
#include "newlib19_malloc.h"

#if __STD_C
Void_t* rEALLOc(RARG Void_t* oldmem, size_t bytes)
#else
Void_t* rEALLOc(RARG oldmem, bytes) RDECL Void_t* oldmem; size_t bytes;
#endif
{
#ifdef MALLOC_PROVIDED

  realloc (oldmem, bytes);

#else

  INTERNAL_SIZE_T    nb;      /* padded request size */

  mchunkptr oldp;             /* chunk corresponding to oldmem */
  INTERNAL_SIZE_T    oldsize; /* its size */

  mchunkptr newp;             /* chunk to return */
  INTERNAL_SIZE_T    newsize; /* its size */
  Void_t*   newmem;           /* corresponding user mem */

  mchunkptr next;             /* next contiguous chunk after oldp */
  INTERNAL_SIZE_T  nextsize;  /* its size */

  mchunkptr prev;             /* previous contiguous chunk before oldp */
  INTERNAL_SIZE_T  prevsize;  /* its size */

  mchunkptr remainder;        /* holds split off extra space from newp */
  INTERNAL_SIZE_T  remainder_size;   /* its size */

  mchunkptr bck;              /* misc temp for linking */
  mchunkptr fwd;              /* misc temp for linking */

#ifdef REALLOC_ZERO_BYTES_FREES
  if (bytes == 0) { fREe(RCALL oldmem); return 0; }
#endif


  /* realloc of null is supposed to be same as malloc */
  if (oldmem == 0) return mALLOc(RCALL bytes);

  MALLOC_LOCK;

  newp    = oldp    = mem2chunk(oldmem);
  newsize = oldsize = chunksize(oldp);


  nb = request2size(bytes);

#if HAVE_MMAP
  if (chunk_is_mmapped(oldp)) 
  {
#if HAVE_MREMAP
    newp = mremap_chunk(oldp, nb);
    if(newp)
    {
      MALLOC_UNLOCK;
      return chunk2mem(newp);
    }
#endif
    /* Note the extra SIZE_SZ overhead. */
    if(oldsize - SIZE_SZ >= nb)
    {
      MALLOC_UNLOCK;
      return oldmem; /* do nothing */
    }
    /* Must alloc, copy, free. */
    newmem = mALLOc(RCALL bytes);
    if (newmem == 0)
    {
      MALLOC_UNLOCK;
      return 0; /* propagate failure */
    }
    MALLOC_COPY(newmem, oldmem, oldsize - 2*SIZE_SZ);
    munmap_chunk(oldp);
    MALLOC_UNLOCK;
    return newmem;
  }
#endif

  check_inuse_chunk(oldp);

  if ((long)(oldsize) < (long)(nb))  
  {

    /* Try expanding forward */

    next = chunk_at_offset(oldp, oldsize);
    if (next == top || !inuse(next)) 
    {
      nextsize = chunksize(next);

      /* Forward into top only if a remainder */
      if (next == top)
      {
        if ((long)(nextsize + newsize) >= (long)(nb + MINSIZE))
        {
          newsize += nextsize;
          top = chunk_at_offset(oldp, nb);
          set_head(top, (newsize - nb) | PREV_INUSE);
          set_head_size(oldp, nb);
	  MALLOC_UNLOCK;
          return chunk2mem(oldp);
        }
      }

      /* Forward into next chunk */
      else if (((long)(nextsize + newsize) >= (long)(nb)))
      { 
        unlink(next, bck, fwd);
        newsize  += nextsize;
        goto split;
      }
    }
    else
    {
      next = 0;
      nextsize = 0;
    }

    /* Try shifting backwards. */

    if (!prev_inuse(oldp))
    {
      prev = prev_chunk(oldp);
      prevsize = chunksize(prev);

      /* try forward + backward first to save a later consolidation */

      if (next != 0)
      {
        /* into top */
        if (next == top)
        {
          if ((long)(nextsize + prevsize + newsize) >= (long)(nb + MINSIZE))
          {
            unlink(prev, bck, fwd);
            newp = prev;
            newsize += prevsize + nextsize;
            newmem = chunk2mem(newp);
            MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
            top = chunk_at_offset(newp, nb);
            set_head(top, (newsize - nb) | PREV_INUSE);
            set_head_size(newp, nb);
	    MALLOC_UNLOCK;
            return newmem;
          }
        }

        /* into next chunk */
        else if (((long)(nextsize + prevsize + newsize) >= (long)(nb)))
        {
          unlink(next, bck, fwd);
          unlink(prev, bck, fwd);
          newp = prev;
          newsize += nextsize + prevsize;
          newmem = chunk2mem(newp);
          MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
          goto split;
        }
      }
      
      /* backward only */
      if (prev != 0 && (long)(prevsize + newsize) >= (long)nb)  
      {
        unlink(prev, bck, fwd);
        newp = prev;
        newsize += prevsize;
        newmem = chunk2mem(newp);
        MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
        goto split;
      }
    }

    /* Must allocate */

    newmem = mALLOc (RCALL bytes);

    if (newmem == 0)  /* propagate failure */
    {
      MALLOC_UNLOCK;
      return 0;
    }

    /* Avoid copy if newp is next chunk after oldp. */
    /* (This can only happen when new chunk is sbrk'ed.) */

    if ( (newp = mem2chunk(newmem)) == next_chunk(oldp)) 
    {
      newsize += chunksize(newp);
      newp = oldp;
      goto split;
    }

    /* Otherwise copy, free, and exit */
    MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
    fREe(RCALL oldmem);
    MALLOC_UNLOCK;
    return newmem;
  }


 split:  /* split off extra room in old or expanded chunk */

  remainder_size = long_sub_size_t(newsize, nb);

  if (remainder_size >= (long)MINSIZE) /* split off remainder */
  {
    remainder = chunk_at_offset(newp, nb);
    set_head_size(newp, nb);
    set_head(remainder, remainder_size | PREV_INUSE);
    set_inuse_bit_at_offset(remainder, remainder_size);
    fREe(RCALL chunk2mem(remainder)); /* let free() deal with it */
  }
  else
  {
    set_head_size(newp, newsize);
    set_inuse_bit_at_offset(newp, newsize);
  }

  check_inuse_chunk(newp);
  MALLOC_UNLOCK;
  return chunk2mem(newp);

#endif /* MALLOC_PROVIDED */
}
