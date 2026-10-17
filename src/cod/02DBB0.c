/* asm/cod/02DBB0.s -> __malloc_lock.
 * Newlib mallocr.c _free_r (authentic fREe); size_t=32-bit, long=64-bit trim_threshold/top_pad, .data attr on the malloc globals
 * MATCHED. */
typedef unsigned int INTERNAL_SIZE_T_02DBB0;
typedef void Void_t_02DBB0;

struct malloc_chunk_02DBB0 {
    INTERNAL_SIZE_T_02DBB0 prev_size;   /* 0x00 */
    INTERNAL_SIZE_T_02DBB0 size;        /* 0x04 */
    struct malloc_chunk_02DBB0 *fd;     /* 0x08 */
    struct malloc_chunk_02DBB0 *bk;     /* 0x0C */
};

typedef struct malloc_chunk_02DBB0 *mchunkptr_02DBB0;
typedef struct malloc_chunk_02DBB0 *mbinptr_02DBB0;

/* The image reaches these globals absolutely (`lui`/`%hi`+`%lo`), never
 * `%gp_rel`, so the .data section attribute keeps `-G8` from putting the
 * 8-byte `unsigned long' tunables into the small-data window. */
#define D_ABS_02DBB0 __attribute__((section(".data")))

extern mbinptr_02DBB0 __malloc_av_[]          D_ABS_02DBB0;
extern unsigned long  __malloc_trim_threshold D_ABS_02DBB0;
extern unsigned long  __malloc_top_pad        D_ABS_02DBB0;

extern void __malloc_lock(void *reent);
extern void __malloc_unlock(void *reent);
extern int  _malloc_trim_r(void *reent, INTERNAL_SIZE_T_02DBB0 pad);

#define SIZE_SZ        (sizeof(INTERNAL_SIZE_T_02DBB0))
#define av_            __malloc_av_
#define trim_threshold __malloc_trim_threshold
#define top_pad        __malloc_top_pad

#define mem2chunk(mem) ((mchunkptr_02DBB0)((char*)(mem) - 2*SIZE_SZ))

#define PREV_INUSE 0x1
#define IS_MMAPPED 0x2
#define SIZE_BITS (PREV_INUSE|IS_MMAPPED)

#define chunksize(p)          ((p)->size & ~(SIZE_BITS))
#define chunk_at_offset(p, s) ((mchunkptr_02DBB0)(((char*)(p)) + (s)))
#define inuse_bit_at_offset(p, s) \
 (((mchunkptr_02DBB0)(((char*)(p)) + (s)))->size & PREV_INUSE)
#define set_head(p, s)        ((p)->size = (s))
#define set_foot(p, s)        (((mchunkptr_02DBB0)((char*)(p) + (s)))->prev_size = (s))

#define bin_at(i)      ((mbinptr_02DBB0)((char*)&(av_[2*(i) + 2]) - 2*SIZE_SZ))
#define top            (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define binblocks      (bin_at(0)->size)

#define bin_index(sz)                                                          \
(((((unsigned long)(sz)) >> 9) ==    0) ?       (((unsigned long)(sz)) >>  3): \
 ((((unsigned long)(sz)) >> 9) <=    4) ?  56 + (((unsigned long)(sz)) >>  6): \
 ((((unsigned long)(sz)) >> 9) <=   20) ?  91 + (((unsigned long)(sz)) >>  9): \
 ((((unsigned long)(sz)) >> 9) <=   84) ? 110 + (((unsigned long)(sz)) >> 12): \
 ((((unsigned long)(sz)) >> 9) <=  340) ? 119 + (((unsigned long)(sz)) >> 15): \
 ((((unsigned long)(sz)) >> 9) <= 1364) ? 124 + (((unsigned long)(sz)) >> 18): \
                                          126)

#define MAX_SMALLBIN_SIZE   512
#define SMALLBIN_WIDTH_BITS 3
#define smallbin_index(sz)  (((unsigned long)(sz)) >> SMALLBIN_WIDTH_BITS)

#define BINBLOCKWIDTH       4
#define idx2binblock(ix)    ((unsigned long)1 << (ix / BINBLOCKWIDTH))
#define mark_binblock(ii)   (binblocks |= idx2binblock(ii))

#define frontlink(P, S, IDX, BK, FD)                                          \
{                                                                             \
  if (S < MAX_SMALLBIN_SIZE)                                                  \
  {                                                                           \
    IDX = smallbin_index(S);                                                  \
    mark_binblock(IDX);                                                       \
    BK = bin_at(IDX);                                                         \
    FD = BK->fd;                                                              \
    P->bk = BK;                                                               \
    P->fd = FD;                                                               \
    FD->bk = BK->fd = P;                                                      \
  }                                                                           \
  else                                                                        \
  {                                                                           \
    IDX = bin_index(S);                                                       \
    BK = bin_at(IDX);                                                         \
    FD = BK->fd;                                                              \
    if (FD == BK) mark_binblock(IDX);                                         \
    else                                                                      \
    {                                                                         \
      while (FD != BK && S < chunksize(FD)) FD = FD->fd;                      \
      BK = FD->bk;                                                            \
    }                                                                         \
    P->bk = BK;                                                               \
    P->fd = FD;                                                               \
    FD->bk = BK->fd = P;                                                      \
  }                                                                           \
}

#define unlink(P, BK, FD)                                                     \
{                                                                             \
  BK = P->bk;                                                                 \
  FD = P->fd;                                                                 \
  FD->bk = BK;                                                                \
  BK->fd = FD;                                                                \
}

#define link_last_remainder(P)                                                \
{                                                                             \
  last_remainder->fd = last_remainder->bk =  P;                               \
  P->fd = P->bk = last_remainder;                                             \
}

#define MALLOC_LOCK   __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)

void _free_r(void *reent_ptr, Void_t_02DBB0 *mem)
{
  mchunkptr_02DBB0 p;         /* chunk corresponding to mem */
  INTERNAL_SIZE_T_02DBB0 hd;  /* its head field */
  INTERNAL_SIZE_T_02DBB0 sz;  /* its size */
  int       idx;              /* its bin index */
  mchunkptr_02DBB0 next;      /* next contiguous chunk */
  INTERNAL_SIZE_T_02DBB0 nextsz; /* its size */
  INTERNAL_SIZE_T_02DBB0 prevsz; /* size of previous contiguous chunk */
  mchunkptr_02DBB0 bck;       /* misc temp for linking */
  mchunkptr_02DBB0 fwd;       /* misc temp for linking */
  int       islr;             /* track whether merging with last_remainder */

  if (mem == 0)                              /* free(0) has no effect */
    return;

  MALLOC_LOCK;

  p = mem2chunk(mem);
  hd = p->size;

  sz = hd & ~PREV_INUSE;
  next = chunk_at_offset(p, sz);
  nextsz = chunksize(next);

  if (next == top)                            /* merge with top */
  {
    sz += nextsz;

    if (!(hd & PREV_INUSE))                    /* consolidate backward */
    {
      prevsz = p->prev_size;
      p = chunk_at_offset(p, -prevsz);
      sz += prevsz;
      unlink(p, bck, fwd);
    }

    set_head(p, sz | PREV_INUSE);
    top = p;
    if ((unsigned long)(sz) >= (unsigned long)trim_threshold)
      _malloc_trim_r(reent_ptr, top_pad);
    MALLOC_UNLOCK;
    return;
  }

  set_head(next, nextsz);                    /* clear inuse bit */

  islr = 0;

  if (!(hd & PREV_INUSE))                    /* consolidate backward */
  {
    prevsz = p->prev_size;
    p = chunk_at_offset(p, -prevsz);
    sz += prevsz;

    if (p->fd == last_remainder)             /* keep as last_remainder */
      islr = 1;
    else
      unlink(p, bck, fwd);
  }

  if (!(inuse_bit_at_offset(next, nextsz)))   /* consolidate forward */
  {
    sz += nextsz;

    if (!islr && next->fd == last_remainder)  /* re-insert last_remainder */
    {
      islr = 1;
      link_last_remainder(p);
    }
    else
      unlink(next, bck, fwd);
  }


  set_head(p, sz | PREV_INUSE);
  set_foot(p, sz);
  if (!islr)
    frontlink(p, sz, idx, bck, fwd);

  MALLOC_UNLOCK;
}
