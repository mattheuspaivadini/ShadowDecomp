/* newlib19_malloc.h - Newlib 1.9.0 stdlib/mallocr.c internals, in the
 * configuration this image was built with.
 *
 * Everything below the configuration block is transcribed verbatim from
 * newlib-1_9_0 newlib/libc/stdlib/mallocr.c (chunk representation, bins, the
 * frontlink/unlink macros, MALLOC_ZERO/MALLOC_COPY). Configuration, confirmed
 * by the already-matched _free_r / _memalign_r / _malloc_trim_r:
 *   INTERNAL_NEWLIB + SEPARATE_OBJECTS (one routine per object, globals extern),
 *   HAVE_MMAP 0, MALLOC_ALIGNMENT 16, SIZE_SZ 4 (INTERNAL_SIZE_T = 32-bit
 *   size_t), SIZE_T_SMALLER_THAN_LONG (long is 64-bit), page size 4096,
 *   USE_MEMCPY (memset/memcpy are the image's func_001283D0/func_0012821C). */
#ifndef NEWLIB19_MALLOC_H
#define NEWLIB19_MALLOC_H

#include "newlib19.h"

#define __STD_C 1
#define Void_t void
#define INTERNAL_NEWLIB
#define SEPARATE_OBJECTS
#define STATIC
#define HAVE_MMAP 0
#define HAVE_MREMAP 0
#define MALLOC_ALIGNMENT 16
#define SIZE_T_SMALLER_THAN_LONG
#define POINTER_UINT unsigned long
#define malloc_getpagesize (4096)
#define assert(x) ((void)0)

extern void __malloc_lock(struct _reent *);
extern void __malloc_unlock(struct _reent *);
extern char *_sbrk_r(struct _reent *, int);

#define MORECORE(size) _sbrk_r(reent_ptr, (size))
#define MORECORE_FAILURE -1
#define MORECORE_CLEARS 0
#define MALLOC_LOCK __malloc_lock(reent_ptr)
#define MALLOC_UNLOCK __malloc_unlock(reent_ptr)

#define RARG struct _reent *reent_ptr,
#define RONEARG struct _reent *reent_ptr
#define RCALL reent_ptr,
#define RONECALL reent_ptr

#define INTERNAL_SIZE_T size_t

#ifdef SIZE_T_SMALLER_THAN_LONG
#define long_sub_size_t(x, y) ( (x < y) ? -((long)(y - x)) : (x - y) );
#else
#define long_sub_size_t(x, y) ( (long)(x - y) )
#endif

#define USE_MEMCPY 1
#if USE_MEMCPY

/* The following macros are only invoked with (2n+1)-multiples of
   INTERNAL_SIZE_T units, with a positive integer n. This is exploited
   for fast inline execution when n is small. */

#define MALLOC_ZERO(charp, nbytes)                                            \
do {                                                                          \
  INTERNAL_SIZE_T mzsz = (nbytes);                                            \
  if(mzsz <= 9*sizeof(mzsz)) {                                                \
    INTERNAL_SIZE_T* mz = (INTERNAL_SIZE_T*) (charp);                         \
    if(mzsz >= 5*sizeof(mzsz)) {     *mz++ = 0;                               \
                                     *mz++ = 0;                               \
      if(mzsz >= 7*sizeof(mzsz)) {   *mz++ = 0;                               \
                                     *mz++ = 0;                               \
        if(mzsz >= 9*sizeof(mzsz)) { *mz++ = 0;                               \
                                     *mz++ = 0; }}}                           \
                                     *mz++ = 0;                               \
                                     *mz++ = 0;                               \
                                     *mz   = 0;                               \
  } else func_001283D0((charp), 0, mzsz);                                            \
} while(0)

#define MALLOC_COPY(dest,src,nbytes)                                          \
do {                                                                          \
  INTERNAL_SIZE_T mcsz = (nbytes);                                            \
  if(mcsz <= 9*sizeof(mcsz)) {                                                \
    INTERNAL_SIZE_T* mcsrc = (INTERNAL_SIZE_T*) (src);                        \
    INTERNAL_SIZE_T* mcdst = (INTERNAL_SIZE_T*) (dest);                       \
    if(mcsz >= 5*sizeof(mcsz)) {     *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
      if(mcsz >= 7*sizeof(mcsz)) {   *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
        if(mcsz >= 9*sizeof(mcsz)) { *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++; }}}                 \
                                     *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
                                     *mcdst   = *mcsrc  ;                     \
  } else func_0012821C(dest, src, mcsz);                                             \
} while(0)
#endif /* USE_MEMCPY */

/* SVID2/XPG mallinfo structure */

struct mallinfo {
  int arena;    /* total space allocated from system */
  int ordblks;  /* number of non-inuse chunks */
  int smblks;   /* unused -- always zero */
  int hblks;    /* number of mmapped regions */
  int hblkhd;   /* total space in mmapped regions */
  int usmblks;  /* unused -- always zero */
  int fsmblks;  /* unused -- always zero */
  int uordblks; /* total allocated space */
  int fordblks; /* total non-inuse space */
  int keepcost; /* top-most, releasable (via malloc_trim) space */
};

#define cALLOc		_calloc_r
#define fREe		_free_r
#define mALLOc		_malloc_r
#define mEMALIGn	_memalign_r
#define rEALLOc		_realloc_r
#define vALLOc		_valloc_r
#define pvALLOc		_pvalloc_r
#define mALLINFo	_mallinfo_r
#define mALLOPt		_mallopt_r

#define malloc_stats			_malloc_stats_r
#define malloc_trim			_malloc_trim_r
#define malloc_usable_size		_malloc_usable_size_r

#define malloc_update_mallinfo		__malloc_update_mallinfo

#define malloc_av_			__malloc_av_
#define malloc_current_mallinfo		__malloc_current_mallinfo
#define malloc_max_sbrked_mem		__malloc_max_sbrked_mem
#define malloc_max_total_mem		__malloc_max_total_mem
#define malloc_sbrk_base		__malloc_sbrk_base
#define malloc_top_pad			__malloc_top_pad
#define malloc_trim_threshold		__malloc_trim_threshold

Void_t* mALLOc(RARG size_t);
void    fREe(RARG Void_t*);
Void_t* rEALLOc(RARG Void_t*, size_t);
Void_t* mEMALIGn(RARG size_t, size_t);
Void_t* cALLOc(RARG size_t, size_t);
int     malloc_trim(RARG size_t);

struct malloc_chunk
{
  INTERNAL_SIZE_T prev_size; /* Size of previous chunk (if free). */
  INTERNAL_SIZE_T size;      /* Size in bytes, including overhead. */
  struct malloc_chunk* fd;   /* double links -- used only if free. */
  struct malloc_chunk* bk;
};

typedef struct malloc_chunk* mchunkptr;

/*

   malloc_chunk details:

    (The following includes lightly edited explanations by Colin Plumb.)

    Chunks of memory are maintained using a `boundary tag' method as
    described in e.g., Knuth or Standish.  (See the paper by Paul
    Wilson ftp://ftp.cs.utexas.edu/pub/garbage/allocsrv.ps for a
    survey of such techniques.)  Sizes of free chunks are stored both
    in the front of each chunk and at the end.  This makes
    consolidating fragmented chunks into bigger chunks very fast.  The
    size fields also hold bits representing whether chunks are free or
    in use.

    An allocated chunk looks like this:  


    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk, if allocated            | |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk, in bytes                         |P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             User data starts here...                          .
            .                                                               .
            .             (malloc_usable_space() bytes)                     .
            .                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk                                     |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


    Where "chunk" is the front of the chunk for the purpose of most of
    the malloc code, but "mem" is the pointer that is returned to the
    user.  "Nextchunk" is the beginning of the next contiguous chunk.

    Chunks always begin on even word boundries, so the mem portion
    (which is returned to the user) is also on an even word boundary, and
    thus double-word aligned.

    Free chunks are stored in circular doubly-linked lists, and look like this:

    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk                            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `head:' |             Size of chunk, in bytes                         |P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Forward pointer to next chunk in list             |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Back pointer to previous chunk in list            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Unused space (may be 0 bytes long)                .
            .                                                               .
            .                                                               |
nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `foot:' |             Size of chunk, in bytes                           |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    The P (PREV_INUSE) bit, stored in the unused low-order bit of the
    chunk size (which is always a multiple of two words), is an in-use
    bit for the *previous* chunk.  If that bit is *clear*, then the
    word before the current chunk size contains the previous chunk
    size, and can be used to find the front of the previous chunk.
    (The very first chunk allocated always has this bit set,
    preventing access to non-existent (or non-owned) memory.)

    Note that the `foot' of the current chunk is actually represented
    as the prev_size of the NEXT chunk. (This makes it easier to
    deal with alignments etc).

    The two exceptions to all this are 

     1. The special chunk `top', which doesn't bother using the 
        trailing size field since there is no
        next contiguous chunk that would have to index off it. (After
        initialization, `top' is forced to always exist.  If it would
        become less than MINSIZE bytes long, it is replenished via
        malloc_extend_top.)

     2. Chunks allocated via mmap, which have the second-lowest-order
        bit (IS_MMAPPED) set in their size fields.  Because they are
        never merged or traversed from any other chunk, they have no
        foot size or inuse information.

    Available chunks are kept in any of several places (all declared below):

    * `av': An array of chunks serving as bin headers for consolidated
       chunks. Each bin is doubly linked.  The bins are approximately
       proportionally (log) spaced.  There are a lot of these bins
       (128). This may look excessive, but works very well in
       practice.  All procedures maintain the invariant that no
       consolidated chunk physically borders another one. Chunks in
       bins are kept in size order, with ties going to the
       approximately least recently used chunk.

       The chunks in each bin are maintained in decreasing sorted order by
       size.  This is irrelevant for the small bins, which all contain
       the same-sized chunks, but facilitates best-fit allocation for
       larger chunks. (These lists are just sequential. Keeping them in
       order almost never requires enough traversal to warrant using
       fancier ordered data structures.)  Chunks of the same size are
       linked with the most recently freed at the front, and allocations
       are taken from the back.  This results in LRU or FIFO allocation
       order, which tends to give each chunk an equal opportunity to be
       consolidated with adjacent freed chunks, resulting in larger free
       chunks and less fragmentation. 

    * `top': The top-most available chunk (i.e., the one bordering the
       end of available memory) is treated specially. It is never
       included in any bin, is used only if no other chunk is
       available, and is released back to the system if it is very
       large (see M_TRIM_THRESHOLD).

    * `last_remainder': A bin holding only the remainder of the
       most recently split (non-top) chunk. This bin is checked
       before other non-fitting chunks, so as to provide better
       locality for runs of sequentially allocated chunks. 

    *  Implicitly, through the host system's memory mapping tables.
       If supported, requests greater than a threshold are usually 
       serviced via calls to mmap, and then later released via munmap.

*/






/*  sizes, alignments */

#define SIZE_SZ                (sizeof(INTERNAL_SIZE_T))
#ifndef MALLOC_ALIGNMENT
#define MALLOC_ALIGN           8
#define MALLOC_ALIGNMENT       (SIZE_SZ + SIZE_SZ)
#else
#define MALLOC_ALIGN           MALLOC_ALIGNMENT
#endif
#define MALLOC_ALIGN_MASK      (MALLOC_ALIGNMENT - 1)
#define MINSIZE                (sizeof(struct malloc_chunk))

/* conversion from malloc headers to user pointers, and back */

#define chunk2mem(p)   ((Void_t*)((char*)(p) + 2*SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char*)(mem) - 2*SIZE_SZ))

/* pad request bytes into a usable size */

#define request2size(req) \
 (((long)((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < \
  (long)(MINSIZE + MALLOC_ALIGN_MASK)) ? ((MINSIZE + MALLOC_ALIGN_MASK) & ~(MALLOC_ALIGN_MASK)) : \
   (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))

/* Check if m has acceptable alignment */

#define aligned_OK(m)    (((unsigned long)((m)) & (MALLOC_ALIGN_MASK)) == 0)




/* 
  Physical chunk operations  
*/


/* size field is or'ed with PREV_INUSE when previous adjacent chunk in use */

#define PREV_INUSE 0x1 

/* size field is or'ed with IS_MMAPPED if the chunk was obtained with mmap() */

#define IS_MMAPPED 0x2

/* Bits to mask off when extracting size */

#define SIZE_BITS (PREV_INUSE|IS_MMAPPED)


/* Ptr to next physical malloc_chunk. */

#define next_chunk(p) ((mchunkptr)( ((char*)(p)) + ((p)->size & ~PREV_INUSE) ))

/* Ptr to previous physical malloc_chunk */

#define prev_chunk(p)\
   ((mchunkptr)( ((char*)(p)) - ((p)->prev_size) ))


/* Treat space at ptr + offset as a chunk */

#define chunk_at_offset(p, s)  ((mchunkptr)(((char*)(p)) + (s)))




/* 
  Dealing with use bits 
*/

/* extract p's inuse bit */

#define inuse(p)\
((((mchunkptr)(((char*)(p))+((p)->size & ~PREV_INUSE)))->size) & PREV_INUSE)

/* extract inuse bit of previous chunk */

#define prev_inuse(p)  ((p)->size & PREV_INUSE)

/* check for mmap()'ed chunk */

#define chunk_is_mmapped(p) ((p)->size & IS_MMAPPED)

/* set/clear chunk as in use without otherwise disturbing */

#define set_inuse(p)\
((mchunkptr)(((char*)(p)) + ((p)->size & ~PREV_INUSE)))->size |= PREV_INUSE

#define clear_inuse(p)\
((mchunkptr)(((char*)(p)) + ((p)->size & ~PREV_INUSE)))->size &= ~(PREV_INUSE)

/* check/set/clear inuse bits in known places */

#define inuse_bit_at_offset(p, s)\
 (((mchunkptr)(((char*)(p)) + (s)))->size & PREV_INUSE)

#define set_inuse_bit_at_offset(p, s)\
 (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE)

#define clear_inuse_bit_at_offset(p, s)\
 (((mchunkptr)(((char*)(p)) + (s)))->size &= ~(PREV_INUSE))




/* 
  Dealing with size fields 
*/

/* Get size, ignoring use bits */

#define chunksize(p)          ((p)->size & ~(SIZE_BITS))

/* Set size at head, without disturbing its use bit */

#define set_head_size(p, s)   ((p)->size = (((p)->size & PREV_INUSE) | (s)))

/* Set size/use ignoring previous bits in header */

#define set_head(p, s)        ((p)->size = (s))

/* Set size at footer (only when chunk is not in use) */

#define set_foot(p, s)   (((mchunkptr)((char*)(p) + (s)))->prev_size = (s))





/*
   Bins

    The bins, `av_' are an array of pairs of pointers serving as the
    heads of (initially empty) doubly-linked lists of chunks, laid out
    in a way so that each pair can be treated as if it were in a
    malloc_chunk. (This way, the fd/bk offsets for linking bin heads
    and chunks are the same).

    Bins for sizes < 512 bytes contain chunks of all the same size, spaced
    8 bytes apart. Larger bins are approximately logarithmically
    spaced. (See the table below.) The `av_' array is never mentioned
    directly in the code, but instead via bin access macros.

    Bin layout:

    64 bins of size       8
    32 bins of size      64
    16 bins of size     512
     8 bins of size    4096
     4 bins of size   32768
     2 bins of size  262144
     1 bin  of size what's left

    There is actually a little bit of slop in the numbers in bin_index
    for the sake of speed. This makes no difference elsewhere.

    The special chunks `top' and `last_remainder' get their own bins,
    (this is implemented via yet more trickery with the av_ array),
    although `top' is never properly linked to its bin since it is
    always handled specially.

*/

#ifdef SEPARATE_OBJECTS
#define av_ malloc_av_
#endif

#define NAV             128   /* number of bins */

typedef struct malloc_chunk* mbinptr;

/* access macros */

#define bin_at(i)      ((mbinptr)((char*)&(av_[2*(i) + 2]) - 2*SIZE_SZ))
#define next_bin(b)    ((mbinptr)((char*)(b) + 2 * sizeof(mbinptr)))
#define prev_bin(b)    ((mbinptr)((char*)(b) - 2 * sizeof(mbinptr)))

/*
   The first 2 bins are never indexed. The corresponding av_ cells are instead
   used for bookkeeping. This is not to save space, but to simplify
   indexing, maintain locality, and avoid some initialization tests.
*/

#define top            (bin_at(0)->fd)   /* The topmost chunk */
#define last_remainder (bin_at(1))       /* remainder from last split */


/*
   Because top initially points to its own bin with initial
   zero size, thus forcing extension on the first malloc request, 
   we avoid having any special code in malloc to check whether 
   it even exists yet. But we still need to in malloc_extend_top.
*/

#define initial_top    ((mchunkptr)(bin_at(0)))

/* Helper macro to initialize bins */

#define IAV(i)  bin_at(i), bin_at(i)

#ifdef DEFINE_MALLOC
STATIC mbinptr av_[NAV * 2 + 2] = {
 0, 0,
 IAV(0),   IAV(1),   IAV(2),   IAV(3),   IAV(4),   IAV(5),   IAV(6),   IAV(7),
 IAV(8),   IAV(9),   IAV(10),  IAV(11),  IAV(12),  IAV(13),  IAV(14),  IAV(15),
 IAV(16),  IAV(17),  IAV(18),  IAV(19),  IAV(20),  IAV(21),  IAV(22),  IAV(23),
 IAV(24),  IAV(25),  IAV(26),  IAV(27),  IAV(28),  IAV(29),  IAV(30),  IAV(31),
 IAV(32),  IAV(33),  IAV(34),  IAV(35),  IAV(36),  IAV(37),  IAV(38),  IAV(39),
 IAV(40),  IAV(41),  IAV(42),  IAV(43),  IAV(44),  IAV(45),  IAV(46),  IAV(47),
 IAV(48),  IAV(49),  IAV(50),  IAV(51),  IAV(52),  IAV(53),  IAV(54),  IAV(55),
 IAV(56),  IAV(57),  IAV(58),  IAV(59),  IAV(60),  IAV(61),  IAV(62),  IAV(63),
 IAV(64),  IAV(65),  IAV(66),  IAV(67),  IAV(68),  IAV(69),  IAV(70),  IAV(71),
 IAV(72),  IAV(73),  IAV(74),  IAV(75),  IAV(76),  IAV(77),  IAV(78),  IAV(79),
 IAV(80),  IAV(81),  IAV(82),  IAV(83),  IAV(84),  IAV(85),  IAV(86),  IAV(87),
 IAV(88),  IAV(89),  IAV(90),  IAV(91),  IAV(92),  IAV(93),  IAV(94),  IAV(95),
 IAV(96),  IAV(97),  IAV(98),  IAV(99),  IAV(100), IAV(101), IAV(102), IAV(103),
 IAV(104), IAV(105), IAV(106), IAV(107), IAV(108), IAV(109), IAV(110), IAV(111),
 IAV(112), IAV(113), IAV(114), IAV(115), IAV(116), IAV(117), IAV(118), IAV(119),
 IAV(120), IAV(121), IAV(122), IAV(123), IAV(124), IAV(125), IAV(126), IAV(127)
};
#else
extern mbinptr av_[NAV * 2 + 2];
#endif



/* field-extraction macros */

#define first(b) ((b)->fd)
#define last(b)  ((b)->bk)

/* 
  Indexing into bins
*/

#define bin_index(sz)                                                          \
(((((unsigned long)(sz)) >> 9) ==    0) ?       (((unsigned long)(sz)) >>  3): \
 ((((unsigned long)(sz)) >> 9) <=    4) ?  56 + (((unsigned long)(sz)) >>  6): \
 ((((unsigned long)(sz)) >> 9) <=   20) ?  91 + (((unsigned long)(sz)) >>  9): \
 ((((unsigned long)(sz)) >> 9) <=   84) ? 110 + (((unsigned long)(sz)) >> 12): \
 ((((unsigned long)(sz)) >> 9) <=  340) ? 119 + (((unsigned long)(sz)) >> 15): \
 ((((unsigned long)(sz)) >> 9) <= 1364) ? 124 + (((unsigned long)(sz)) >> 18): \
                                          126)                     
/* 
  bins for chunks < 512 are all spaced SMALLBIN_WIDTH bytes apart, and hold
  identically sized chunks. This is exploited in malloc.
*/

#define MAX_SMALLBIN_SIZE   512
#define SMALLBIN_WIDTH        8
#define SMALLBIN_WIDTH_BITS   3
#define MAX_SMALLBIN        (MAX_SMALLBIN_SIZE / SMALLBIN_WIDTH) - 1

#define smallbin_index(sz)  (((unsigned long)(sz)) >> SMALLBIN_WIDTH_BITS)

/* 
   Requests are `small' if both the corresponding and the next bin are small
*/

#define is_small_request(nb) (nb < MAX_SMALLBIN_SIZE - SMALLBIN_WIDTH)



/*
    To help compensate for the large number of bins, a one-level index
    structure is used for bin-by-bin searching.  `binblocks' is a
    one-word bitvector recording whether groups of BINBLOCKWIDTH bins
    have any (possibly) non-empty bins, so they can be skipped over
    all at once during during traversals. The bits are NOT always
    cleared as soon as all bins in a block are empty, but instead only
    when all are noticed to be empty during traversal in malloc.
*/

#define BINBLOCKWIDTH     4   /* bins per block */

#define binblocks      (bin_at(0)->size) /* bitvector of nonempty blocks */

/* bin<->block macros */

#define idx2binblock(ix)    ((unsigned long)1 << (ix / BINBLOCKWIDTH))
#define mark_binblock(ii)   (binblocks |= idx2binblock(ii))
#define clear_binblock(ii)  (binblocks &= ~(idx2binblock(ii)))





/*  Other static bookkeeping data */

#ifdef SEPARATE_OBJECTS
#define trim_threshold		malloc_trim_threshold
#define top_pad			malloc_top_pad
#define n_mmaps_max		malloc_n_mmaps_max
#define mmap_threshold		malloc_mmap_threshold
#define sbrk_base		malloc_sbrk_base
#define max_sbrked_mem		malloc_max_sbrked_mem
#define max_total_mem		malloc_max_total_mem
#define current_mallinfo	malloc_current_mallinfo
#define n_mmaps			malloc_n_mmaps
#define max_n_mmaps		malloc_max_n_mmaps
#define mmapped_mem		malloc_mmapped_mem
#define max_mmapped_mem		malloc_max_mmapped_mem
#endif

/* variables holding tunable values */

#ifdef DEFINE_MALLOC

STATIC unsigned long trim_threshold   = DEFAULT_TRIM_THRESHOLD;
STATIC unsigned long top_pad          = DEFAULT_TOP_PAD;
#if HAVE_MMAP
STATIC unsigned int  n_mmaps_max      = DEFAULT_MMAP_MAX;
STATIC unsigned long mmap_threshold   = DEFAULT_MMAP_THRESHOLD;
#endif

/* The first value returned from sbrk */
STATIC char* sbrk_base = (char*)(-1);

/* The maximum memory obtained from system via sbrk */
STATIC unsigned long max_sbrked_mem = 0; 

/* The maximum via either sbrk or mmap */
STATIC unsigned long max_total_mem = 0; 

/* internal working copy of mallinfo */
STATIC struct mallinfo current_mallinfo = {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#if HAVE_MMAP

/* Tracking mmaps */

STATIC unsigned int n_mmaps = 0;
STATIC unsigned int max_n_mmaps = 0;
STATIC unsigned long mmapped_mem = 0;
STATIC unsigned long max_mmapped_mem = 0;

#endif

#else /* ! DEFINE_MALLOC */

extern unsigned long trim_threshold NL19_DATA;
extern unsigned long top_pad NL19_DATA;
#if HAVE_MMAP
extern unsigned int  n_mmaps_max;
extern unsigned long mmap_threshold;
#endif
extern char* sbrk_base NL19_DATA;
extern unsigned long max_sbrked_mem NL19_DATA;
extern unsigned long max_total_mem NL19_DATA;
extern struct mallinfo current_mallinfo NL19_DATA;
#if HAVE_MMAP
extern unsigned int n_mmaps;
extern unsigned int max_n_mmaps;
extern unsigned long mmapped_mem;
extern unsigned long max_mmapped_mem;
#endif

#endif /* ! DEFINE_MALLOC */

/* The total memory obtained from system via sbrk */
#define sbrked_mem  (current_mallinfo.arena)



/* 
  Debugging support 
*/

#if DEBUG


/*
  These routines make a number of assertions about the states
  of data structures that should be true at all times. If any
  are not true, it's very likely that a user program has somehow
  trashed memory. (It's also possible that there is a coding error
  in malloc. In which case, please report it!)
*/

#if __STD_C
static void do_check_chunk(mchunkptr p) 
#else
static void do_check_chunk(p) mchunkptr p;
#endif
{ 
  INTERNAL_SIZE_T sz = p->size & ~PREV_INUSE;

  /* No checkable chunk is mmapped */
  assert(!chunk_is_mmapped(p));

  /* Check for legal address ... */
  assert((char*)p >= sbrk_base);
  if (p != top) 
    assert((char*)p + sz <= (char*)top);
  else
    assert((char*)p + sz <= sbrk_base + sbrked_mem);

}


#if __STD_C
static void do_check_free_chunk(mchunkptr p) 
#else
static void do_check_free_chunk(p) mchunkptr p;
#endif
{ 
  INTERNAL_SIZE_T sz = p->size & ~PREV_INUSE;
  mchunkptr next = chunk_at_offset(p, sz);

  do_check_chunk(p);

  /* Check whether it claims to be free ... */
  assert(!inuse(p));

  /* Unless a special marker, must have OK fields */
  if ((long)sz >= (long)MINSIZE)
  {
    assert((sz & MALLOC_ALIGN_MASK) == 0);
    assert(aligned_OK(chunk2mem(p)));
    /* ... matching footer field */
    assert(next->prev_size == sz);
    /* ... and is fully consolidated */
    assert(prev_inuse(p));
    assert (next == top || inuse(next));
    
    /* ... and has minimally sane links */
    assert(p->fd->bk == p);
    assert(p->bk->fd == p);
  }
  else /* markers are always of size SIZE_SZ */
    assert(sz == SIZE_SZ); 
}

#if __STD_C
static void do_check_inuse_chunk(mchunkptr p) 
#else
static void do_check_inuse_chunk(p) mchunkptr p;
#endif
{ 
  mchunkptr next = next_chunk(p);
  do_check_chunk(p);

  /* Check whether it claims to be in use ... */
  assert(inuse(p));

  /* ... and is surrounded by OK chunks.
    Since more things can be checked with free chunks than inuse ones,
    if an inuse chunk borders them and debug is on, it's worth doing them.
  */
  if (!prev_inuse(p)) 
  {
    mchunkptr prv = prev_chunk(p);
    assert(next_chunk(prv) == p);
    do_check_free_chunk(prv);
  }
  if (next == top)
  {
    assert(prev_inuse(next));
    assert(chunksize(next) >= MINSIZE);
  }
  else if (!inuse(next))
    do_check_free_chunk(next);

}

#if __STD_C
static void do_check_malloced_chunk(mchunkptr p, INTERNAL_SIZE_T s) 
#else
static void do_check_malloced_chunk(p, s) mchunkptr p; INTERNAL_SIZE_T s;
#endif
{
  INTERNAL_SIZE_T sz = p->size & ~PREV_INUSE;
  long room = long_sub_size_t(sz, s);

  do_check_inuse_chunk(p);

  /* Legal size ... */
  assert((long)sz >= (long)MINSIZE);
  assert((sz & MALLOC_ALIGN_MASK) == 0);
  assert(room >= 0);
  assert(room < (long)MINSIZE);

  /* ... and alignment */
  assert(aligned_OK(chunk2mem(p)));


  /* ... and was allocated at front of an available chunk */
  assert(prev_inuse(p));

}


#define check_free_chunk(P)  do_check_free_chunk(P)
#define check_inuse_chunk(P) do_check_inuse_chunk(P)
#define check_chunk(P) do_check_chunk(P)
#define check_malloced_chunk(P,N) do_check_malloced_chunk(P,N)
#else
#define check_free_chunk(P) 
#define check_inuse_chunk(P)
#define check_chunk(P)
#define check_malloced_chunk(P,N)
#endif



/* 
  Macro-based internal utilities
*/


/*  
  Linking chunks in bin lists.
  Call these only with variables, not arbitrary expressions, as arguments.
*/

/* 
  Place chunk p of size s in its bin, in size order,
  putting it ahead of others of same size.
*/


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


/* take a chunk off a list */

#define unlink(P, BK, FD)                                                     \
{                                                                             \
  BK = P->bk;                                                                 \
  FD = P->fd;                                                                 \
  FD->bk = BK;                                                                \
  BK->fd = FD;                                                                \
}                                                                             \

/* Place p as the last remainder */

#define link_last_remainder(P)                                                \
{                                                                             \
  last_remainder->fd = last_remainder->bk =  P;                               \
  P->fd = P->bk = last_remainder;                                             \
}

/* Clear the last_remainder bin */

#define clear_last_remainder \
  (last_remainder->fd = last_remainder->bk = last_remainder)


#endif /* NEWLIB19_MALLOC_H */
