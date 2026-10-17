/* asm/cod/0266F0.s -> extract_cie_info.
 * GCC frame.c/frame-dwarf2.c extract_cie_info (authentic source)
 * MATCHED. */
#include "frame2000.h"

/* the augmentation literals, by their image labels (.rodata) */
extern const char D_00139250[];	/* "" */
extern const char D_00139258[];	/* "eh" */

void *
extract_cie_info (fde *f, struct cie_info *c)
{
  void *p;
  int i;

  c->augmentation = get_cie (f)->augmentation;

  if (strcmp (c->augmentation, D_00139250) != 0
      && strcmp (c->augmentation, D_00139258) != 0
      && c->augmentation[0] != 'z')
    return 0;

  p = c->augmentation + strlen (c->augmentation) + 1;

  if (strcmp (c->augmentation, D_00139258) == 0)
    {
      c->eh_ptr = read_pointer (p);
      p += sizeof (void *);
    }
  else
    c->eh_ptr = 0;

  p = decode_uleb128 (p, &c->code_align);
  p = decode_sleb128 (p, &c->data_align);
  c->ra_regno = *(unsigned char *)p++;

  /* If the augmentation starts with 'z', we now see the length of the
     augmentation fields.  */
  if (c->augmentation[0] == 'z')
    {
      p = decode_uleb128 (p, &i);
      p += i;
    }

  return p;
}
