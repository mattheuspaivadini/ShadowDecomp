/* asm/cod/024F48.s -> __do_global_ctors.
 * GCC 2000 libgcc2.c L__main __do_global_ctors (authentic source)
 * MATCHED. */
/* gcc gbl-ctors.h */
typedef void (*func_ptr) (void);
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

#define DO_GLOBAL_CTORS_BODY						do {									  unsigned long nptrs = (unsigned long) __CTOR_LIST__[0];		  unsigned i;								  if (nptrs == (unsigned long)-1)				            for (nptrs = 0; __CTOR_LIST__[nptrs + 1] != 0; nptrs++);		  for (i = nptrs; i >= 1; i--)						    __CTOR_LIST__[i] ();						} while (0) 

/* gcc frame.h */
typedef unsigned int size_t;
struct object {
  void *pc_begin;
  void *pc_end;
  struct dwarf_fde *fde_begin;
  struct dwarf_fde **fde_array;
  size_t count;
  struct object *next;
};
extern void __register_frame_info (void *, struct object *);
extern void *__deregister_frame_info (void *);

extern unsigned char __EH_FRAME_BEGIN__[];

extern int func_00127460 (void (*) (void));	/* atexit (027460) */
#define atexit func_00127460
extern void __do_global_dtors (void);

extern struct object D_00169F70;	/* static struct object object; */

void
__do_global_ctors (void)
{
  {
    __register_frame_info (__EH_FRAME_BEGIN__, &D_00169F70);
  }
  DO_GLOBAL_CTORS_BODY;
  atexit (__do_global_dtors);
}
