/* asm/cod/0261D8.s -> abort.
 * GCC frame.c/frame-dwarf2.c __deregister_frame_info (2000 fde_array test, SCE sema) (authentic source)
 * MATCHED. */
typedef unsigned int size_t;
extern void *malloc (size_t);
extern void free (void *);

/* gcc frame.h */
struct object {
  void *pc_begin;
  void *pc_end;
  struct dwarf_fde *fde_begin;
  struct dwarf_fde **fde_array;
  size_t count;
  struct object *next;
};

/* frame.c `static struct object *objects;' - the image's D_00169F90 */
extern struct object *D_00169F90[];
#define objects (D_00169F90[0])

/* The SCE gthr layer: the object mutex is the __sce_eh_sema_id semaphore. */
extern int __sce_eh_sema_id[];
extern int WaitSema (int);
extern int SignalSema (int);
#define init_object_mutex_once()
#define __gthread_mutex_lock(m) WaitSema (__sce_eh_sema_id[0])
#define __gthread_mutex_unlock(m) SignalSema (__sce_eh_sema_id[0])

extern void func_00127448 (void) __attribute__ ((noreturn));	/* abort (027448) */
#define abort func_00127448

void *
__deregister_frame_info (void *begin)
{
  struct object **p;

  init_object_mutex_once ();
  __gthread_mutex_lock (&object_mutex);

  p = &objects;
  while (*p)
    {
      if ((*p)->fde_begin == begin)
	{
	  struct object *ob = *p;
	  *p = (*p)->next;

	  /* If we've run init_frame for this object, free the FDE array.  */
	  if (ob->fde_array && ob->fde_array != begin)
	    free (ob->fde_array);

	  __gthread_mutex_unlock (&object_mutex);
	  return (void *) ob;
	}
      p = &((*p)->next);
    }

  __gthread_mutex_unlock (&object_mutex);
  abort ();
}
