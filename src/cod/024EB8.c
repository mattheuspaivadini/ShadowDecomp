/* asm/cod/024EB8.s -> __do_global_dtors.
 * GCC 2000 libgcc2.c L__main __do_global_dtors (authentic source)
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

/* the function-statics of the L__main object, by their image labels */
extern func_ptr *D_00135964 __attribute__((section(".data")));	/* static func_ptr *p = __DTOR_LIST__ + 1; */
extern int D_00135968 __attribute__((section(".data")));	/* static int completed = 0; */
#define p D_00135964
#define completed D_00135968

void
__do_global_dtors (void)
{
  while (*p)
    {
      p++;
      (*(p-1)) ();
    }
  {
    if (! completed)
      {
	completed = 1;
	__deregister_frame_info (__EH_FRAME_BEGIN__);
      }
  }
}
