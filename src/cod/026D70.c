/* asm/cod/026D70.s -> __frame_state_for.
 * GCC frame.c/frame-dwarf2.c __frame_state_for (authentic source)
 * MATCHED. */
#include "frame2000.h"

struct frame_state *
__frame_state_for (void *pc_target, struct frame_state *state_in)
{
  fde *f;
  void *insn, *end, *pc;
  struct cie_info info;
  struct frame_state_internal state;

  f = find_fde (pc_target);
  if (f == 0)
    return 0;

  insn = extract_cie_info (f, &info);
  if (insn == 0)
    return 0;

  memset (&state, 0, sizeof (state));
  state.s.retaddr_column = info.ra_regno;
  state.s.eh_ptr = info.eh_ptr;

  /* First decode all the insns in the CIE.  */
  end = next_fde ((fde*) get_cie (f));
  while (insn < end)
    insn = execute_cfa_insn (insn, &state, &info, 0);

  insn = ((fde *)f) + 1;

  if (info.augmentation[0] == 'z')
    {
      int i;
      insn = decode_uleb128 (insn, &i);
      insn += i;
    }

  /* Then the insns in the FDE up to our target PC.  */
  end = next_fde (f);
  pc = f->pc_begin;
  while (insn < end && pc <= pc_target)
    insn = execute_cfa_insn (insn, &state, &info, &pc);

  /* the image expands this copy inline: the builtin, not the libc memcpy */
  __builtin_memcpy (state_in, &state.s, sizeof (state.s));
  return state_in;
}
