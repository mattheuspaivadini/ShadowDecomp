/* frame2000.h - the GCC frame.c / frame-dwarf2.c internals (DWARF2 unwind
 * registry) in the revision the EE libgcc was built from: gcc mainline of
 * 2000-06 (gcc-mirror 89d7f003, "frame.c (end_fde_sort): Remove extraneous
 * erratic array test"), the base of 2.96. Everything from `sword' down is
 * transcribed from that revision's frame.h / frame-dwarf2.c / frame.c.
 *
 * SCE adaptations, all read off the image: the object mutex is the
 * __sce_eh_sema_id semaphore (WaitSema/SignalSema); FIRST_PSEUDO_REGISTER
 * is 123 (frame_state_internal is 0x480 bytes with 8-byte longs); the
 * file-statics `objects' and fde_split's `marker' are the image's
 * D_00169F90 / D_00169F8C; the out-of-line statics keep their splat labels. */
#ifndef FRAME2000_H
#define FRAME2000_H

typedef unsigned int size_t;
#ifndef NULL
#define NULL 0
#endif
extern void *malloc (size_t);
extern void free (void *);
extern void *func_001283D0 (void *, int, size_t);	/* memset */
extern void *func_0012821C (void *, const void *, size_t);	/* memcpy */
#define memset func_001283D0
#define memcpy func_0012821C
extern int func_00128E6C (const char *, const char *);	/* strcmp */
extern size_t func_001290C4 (const char *);	/* strlen */
#define strcmp func_00128E6C
#define strlen func_001290C4
extern void func_00127448 (void) __attribute__ ((noreturn));	/* abort */
#define abort func_00127448

extern int __sce_eh_sema_id[];
extern int WaitSema (int);
extern int SignalSema (int);
#define init_object_mutex_once()
#define __gthread_mutex_lock(m) WaitSema (__sce_eh_sema_id[0])
#define __gthread_mutex_unlock(m) SignalSema (__sce_eh_sema_id[0])

#define FIRST_PSEUDO_REGISTER 123
#define DWARF_FRAME_REGISTERS FIRST_PSEUDO_REGISTER

typedef struct frame_state
{
  void *cfa;
  void *eh_ptr;
  long cfa_offset;
  long args_size;
  long reg_or_offset[DWARF_FRAME_REGISTERS+1];
  unsigned short cfa_reg;
  unsigned short retaddr_column;
  char saved[DWARF_FRAME_REGISTERS+1];
} frame_state;

#define REG_UNSAVED 0
#define REG_SAVED_OFFSET 1
#define REG_SAVED_REG 2

struct object {
  void *pc_begin;
  void *pc_end;
  struct dwarf_fde *fde_begin;
  struct dwarf_fde **fde_array;
  size_t count;
  struct object *next;
};

typedef          int  sword __attribute__ ((mode (SI)));
typedef unsigned int  uword __attribute__ ((mode (SI)));
typedef unsigned int  uaddr __attribute__ ((mode (pointer)));
typedef          int  saddr __attribute__ ((mode (pointer)));
typedef unsigned char ubyte;

/* Terminology:
   CIE - Common Information Element
   FDE - Frame Descriptor Element

   There is one per function, and it describes where the function code
   is located, and what the register lifetimes and stack layout are
   within the function.

   The data structures are defined in the DWARF specfication, although
   not in a very readable way (see LITERATURE).

   Every time an exception is thrown, the code needs to locate the FDE
   for the current function, and starts to look for exception regions
   from that FDE. This works in a two-level search:
   a) in a linear search, find the shared image (i.e. DLL) containing
      the PC
   b) using the FDE table for that shared object, locate the FDE using
      binary search (which requires the sorting).  */   

/* The first few fields of a CIE.  The CIE_id field is 0 for a CIE,
   to distinguish it from a valid FDE.  FDEs are aligned to an addressing
   unit boundary, but the fields within are unaligned.  */

struct dwarf_cie {
  uword length;
  sword CIE_id;
  ubyte version;
  char augmentation[0];
} __attribute__ ((packed, aligned (__alignof__ (void *))));

/* The first few fields of an FDE.  */

struct dwarf_fde {
  uword length;
  sword CIE_delta;
  void* pc_begin;
  uaddr pc_range;
} __attribute__ ((packed, aligned (__alignof__ (void *))));

typedef struct dwarf_fde fde;

/* Objects to be searched for frame unwind info.  */

extern struct object *D_00169F90[];	/* static struct object *objects; */
#define objects (D_00169F90[0])

struct cie_info {
  char *augmentation;
  void *eh_ptr;
  int code_align;
  int data_align;
  unsigned ra_regno;
};

/* The current unwind state, plus a saved copy for DW_CFA_remember_state.  */

struct frame_state_internal
{
  struct frame_state s;
  struct frame_state_internal *saved_state;
};

/* This is undefined below if we need it to be an actual function.  */
typedef struct fde_vector
{
  fde **array;
  size_t count;
} fde_vector;

typedef struct fde_accumulator
{
  fde_vector linear;
  fde_vector erratic;
} fde_accumulator;

extern fde *D_00169F8C[];	/* fde_split: static fde *marker; */
#define marker (D_00169F8C[0])

/* out-of-line file-statics, by their splat labels */
#define decode_uleb128 func_00125998
#define decode_sleb128 func_001259E0
#define fde_merge func_00125A38
#define end_fde_sort func_00125B30
#define count_fdes func_001262B8
#define add_fdes func_001262F8
#define search_fdes func_00126388
#define frame_init func_001263E0
#define find_fde func_00126548
#define extract_cie_info func_001266F0
#define execute_cfa_insn func_00126920

void *decode_uleb128 (unsigned char *buf, unsigned *r);
void *decode_sleb128 (unsigned char *buf, int *r);
void fde_merge (fde_vector *v1, const fde_vector *v2);
fde **end_fde_sort (fde_accumulator *accu, size_t count);
size_t count_fdes (fde *this_fde);
void add_fdes (fde *this_fde, fde_accumulator *accu, void **beg_ptr, void **end_ptr);
fde *search_fdes (fde *this_fde, void *pc);
void frame_init (struct object* ob);
fde *find_fde (void *pc);
void *extract_cie_info (fde *f, struct cie_info *c);
void *execute_cfa_insn (void *p, struct frame_state_internal *state, struct cie_info *info, void **pc);

union unaligned {
  void *p;
  unsigned b2 __attribute__ ((mode (HI)));
  unsigned b4 __attribute__ ((mode (SI)));
  unsigned b8 __attribute__ ((mode (DI)));
} __attribute__ ((packed));

static inline void *
read_pointer (void *p)
{ union unaligned *up = p; return up->p; }
static inline unsigned
read_1byte (void *p)
{ return *(unsigned char *)p; }
static inline unsigned
read_2byte (void *p)
{ union unaligned *up = p; return up->b2; }
static inline unsigned
read_4byte (void *p)
{ union unaligned *up = p; return up->b4; }
static inline unsigned long
read_8byte (void *p)
{ union unaligned *up = p; return up->b8; }

/* Ordering function for FDEs.  Functions can't overlap, so we just compare
   their starting addresses.  */

static inline saddr
fde_compare (fde *x, fde *y)
{
  return (saddr)x->pc_begin - (saddr)y->pc_begin;
}

/* Return the address of the FDE after P.  */

static inline fde *
next_fde (fde *p)
{
  return (fde *)(((char *)p) + p->length + sizeof (p->length));
}


static inline int
start_fde_sort (fde_accumulator *accu, size_t count)
{
  accu->linear.array = count ? (fde **) malloc (sizeof (fde *) * count) : NULL;
  accu->erratic.array = accu->linear.array ?
      (fde **) malloc (sizeof (fde *) * count) : NULL;
  accu->linear.count = 0;
  accu->erratic.count = 0;
  
  return accu->linear.array != NULL;
}

static inline void
fde_insert (fde_accumulator *accu, fde *this_fde)
{
  if (accu->linear.array)
    accu->linear.array[accu->linear.count++] = this_fde;
}

/* Split LINEAR into a linear sequence with low values and an erratic
   sequence with high values, put the linear one (of longest possible
   length) into LINEAR and the erratic one into ERRATIC. This is O(N).
   
   Because the longest linear sequence we are trying to locate within the
   incoming LINEAR array can be interspersed with (high valued) erratic
   entries.  We construct a chain indicating the sequenced entries.
   To avoid having to allocate this chain, we overlay it onto the space of
   the ERRATIC array during construction.  A final pass iterates over the
   chain to determine what should be placed in the ERRATIC array, and
   what is the linear sequence.  This overlay is safe from aliasing.  */
static inline void
fde_split (fde_vector *linear, fde_vector *erratic)
{
  size_t count = linear->count;
  fde **chain_end = &marker;
  size_t i, j, k;

  /* This should optimize out, but it is wise to make sure this assumption
     is correct. Should these have different sizes, we cannot cast between
     them and the overlaying onto ERRATIC will not work.  */
  if (sizeof (fde *) != sizeof (fde **))
    abort ();
  
  for (i = 0; i < count; i++)
    {
      fde **probe;
      
      for (probe = chain_end;
           probe != &marker && fde_compare (linear->array[i], *probe) < 0;
           probe = chain_end)
        {
          chain_end = (fde **)erratic->array[probe - linear->array];
          erratic->array[probe - linear->array] = NULL;
        }
      erratic->array[i] = (fde *)chain_end;
      chain_end = &linear->array[i];
    }

  /* Each entry in LINEAR which is part of the linear sequence we have
     discovered will correspond to a non-NULL entry in the chain we built in
     the ERRATIC array.  */
  for (i = j = k = 0; i < count; i++)
    if (erratic->array[i])
      linear->array[j++] = linear->array[i];
    else
      erratic->array[k++] = linear->array[i];
  linear->count = j;
  erratic->count = k;
}

/* This is O(n log(n)).  BSD/OS defines heapsort in stdlib.h, so we must
   use a name that does not conflict.  */
static inline void
frame_heapsort (fde_vector *erratic)
{
  /* For a description of this algorithm, see:
     Samuel P. Harbison, Guy L. Steele Jr.: C, a reference manual, 2nd ed.,
     p. 60-61. */
  fde ** a = erratic->array;
  /* A portion of the array is called a "heap" if for all i>=0:
     If i and 2i+1 are valid indices, then a[i] >= a[2i+1].
     If i and 2i+2 are valid indices, then a[i] >= a[2i+2]. */
#define SWAP(x,y) do { fde * tmp = x; x = y; y = tmp; } while (0)
  size_t n = erratic->count;
  size_t m = n;
  size_t i;

  while (m > 0)
    {
      /* Invariant: a[m..n-1] is a heap. */
      m--;
      for (i = m; 2*i+1 < n; )
        {
          if (2*i+2 < n
              && fde_compare (a[2*i+2], a[2*i+1]) > 0
              && fde_compare (a[2*i+2], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+2]);
              i = 2*i+2;
            }
          else if (fde_compare (a[2*i+1], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+1]);
              i = 2*i+1;
            }
          else
            break;
        }
    }
  while (n > 1)
    {
      /* Invariant: a[0..n-1] is a heap. */
      n--;
      SWAP (a[0], a[n]);
      for (i = 0; 2*i+1 < n; )
        {
          if (2*i+2 < n
              && fde_compare (a[2*i+2], a[2*i+1]) > 0
              && fde_compare (a[2*i+2], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+2]);
              i = 2*i+2;
            }
          else if (fde_compare (a[2*i+1], a[i]) > 0)
            {
              SWAP (a[i], a[2*i+1]);
              i = 2*i+1;
            }
          else
            break;
        }
    }
#undef SWAP
}

/* Merge V1 and V2, both sorted, and put the result into V1. */
static inline struct dwarf_cie *
get_cie (fde *f)
{
  return ((void *)&f->CIE_delta) - f->CIE_delta;
}

#endif /* FRAME2000_H */
