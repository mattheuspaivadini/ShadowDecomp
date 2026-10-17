/* asm/cod/0275A0.s -> _memalign_r @ 0x001275A0 (0x1C8 bytes, 114 insns).
 * Newlib mallocr.c mEMALIGn (authentic old-Newlib source, HAVE_MMAP=0).
 * size_t=32-bit, long=64-bit, MALLOC_ALIGNMENT=2*sizeof(double)=16, MINSIZE=16,
 * SIZE_SZ=4; no `nb > INT_MAX || nb < bytes' overflow guard in this revision.
 * MATCHED. */
typedef unsigned int size_t_0275A0;
typedef unsigned int INTERNAL_SIZE_T_0275A0;
typedef void Void_t_0275A0;

struct malloc_chunk_0275A0 {
    INTERNAL_SIZE_T_0275A0 prev_size;   /* 0x00 */
    INTERNAL_SIZE_T_0275A0 size;        /* 0x04 */
    struct malloc_chunk_0275A0 *fd;     /* 0x08 */
    struct malloc_chunk_0275A0 *bk;     /* 0x0C */
};

typedef struct malloc_chunk_0275A0 *mchunkptr_0275A0;

extern void  __malloc_lock(void *reent);
extern void  __malloc_unlock(void *reent);
extern void *_malloc_r(void *reent, size_t_0275A0 size);
extern void  _free_r(void *reent, void *p);

#define SIZE_SZ                (sizeof(INTERNAL_SIZE_T_0275A0))
#define MALLOC_ALIGNMENT       ((size_t_0275A0)(2 * sizeof(double)))
#define MALLOC_ALIGN_MASK      (MALLOC_ALIGNMENT - 1)
#define MINSIZE                (sizeof(struct malloc_chunk_0275A0))

#define chunk2mem(p)   ((Void_t_0275A0*)((char*)(p) + 2*SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr_0275A0)((char*)(mem) - 2*SIZE_SZ))

#define PREV_INUSE 0x1
#define IS_MMAPPED 0x2
#define SIZE_BITS (PREV_INUSE|IS_MMAPPED)

#define chunksize(p)          ((p)->size & ~(SIZE_BITS))
#define set_head_size(p, s)   ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define set_head(p, s)        ((p)->size = (s))
#define set_inuse_bit_at_offset(p, s) \
 (((mchunkptr_0275A0)(((char*)(p)) + (s)))->size |= PREV_INUSE)
#define chunk_at_offset(p, s) ((mchunkptr_0275A0)(((char*)(p)) + (s)))

#define request2size(req) \
 (((unsigned long)((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < \
  (unsigned long)(MINSIZE + MALLOC_ALIGN_MASK)) ? ((MINSIZE + MALLOC_ALIGN_MASK) & ~(MALLOC_ALIGN_MASK)) : \
   (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))

#define long_sub_size_t(x, y)                             \
  (sizeof (long) > sizeof (INTERNAL_SIZE_T_0275A0) && x < y \
   ? -(long) (y - x)                                      \
   : (long) (x - y))

#define MALLOC_LOCK   __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)

Void_t_0275A0 *_memalign_r(void *reent_ptr, size_t_0275A0 alignment,
                           size_t_0275A0 bytes)
{
  INTERNAL_SIZE_T_0275A0 nb;       /* padded request size */
  char*     m;                     /* memory returned by malloc call */
  mchunkptr_0275A0 p;              /* corresponding chunk */
  char*     brk;                   /* alignment point within p */
  mchunkptr_0275A0 newp;           /* chunk to return */
  INTERNAL_SIZE_T_0275A0 newsize;  /* its size */
  INTERNAL_SIZE_T_0275A0 leadsize; /* leading space before alignment point */
  mchunkptr_0275A0 remainder;      /* spare room at end to split off */
  long      remainder_size;        /* its size */

  /* If need less alignment than we give anyway, just relay to malloc */

  if (alignment <= MALLOC_ALIGNMENT) return _malloc_r(reent_ptr, bytes);

  /* Otherwise, ensure that it is at least a minimum chunk size */

  if (alignment <  MINSIZE) alignment = MINSIZE;

  /* Call malloc with worst case padding to hit alignment. */

  nb = request2size(bytes);

  m  = (char*)(_malloc_r(reent_ptr, nb + alignment + MINSIZE));

  if (m == 0) return 0; /* propagate failure */

  MALLOC_LOCK;

  p = mem2chunk(m);

  if ((((unsigned long)(m)) % alignment) == 0) /* aligned */
  {
    /* HAVE_MMAP is 0 in this build; nothing to do */
  }
  else /* misaligned */
  {
    /*
      Find an aligned spot inside chunk.
      Since we need to give back leading space in a chunk of at
      least MINSIZE, if the first calculation places us at
      a spot with less than MINSIZE leader, we can move to the
      next aligned spot -- we've allocated enough total room so that
      this is always possible.
    */

    brk = (char*)mem2chunk(((unsigned long)(m + alignment - 1)) & -alignment);
    if ((long)(brk - (char*)(p)) < (long)MINSIZE) brk = brk + alignment;

    newp = (mchunkptr_0275A0)brk;
    leadsize = brk - (char*)(p);
    newsize = chunksize(p) - leadsize;

    /* give back leader, use the rest */

    set_head(newp, newsize | PREV_INUSE);
    set_inuse_bit_at_offset(newp, newsize);
    set_head_size(p, leadsize);
    _free_r(reent_ptr, chunk2mem(p));
    p = newp;
  }

  /* Also give back spare room at the end */

  remainder_size = long_sub_size_t(chunksize(p), nb);

  if (remainder_size >= (long)MINSIZE)
  {
    remainder = chunk_at_offset(p, nb);
    set_head(remainder, remainder_size | PREV_INUSE);
    set_head_size(p, nb);
    _free_r(reent_ptr, chunk2mem(remainder));
  }

  MALLOC_UNLOCK;
  return chunk2mem(p);
}
