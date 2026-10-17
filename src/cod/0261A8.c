/* asm/cod/0261A8.s -> __register_frame_table.
 * GCC frame.c/frame-dwarf2.c __register_frame_table (authentic source)
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

extern void __register_frame_info_table (void *, struct object *);

void
__register_frame_table (void *begin)
{
  struct object *ob = (struct object *) malloc (sizeof (struct object));
  __register_frame_info_table (begin, ob);
}
