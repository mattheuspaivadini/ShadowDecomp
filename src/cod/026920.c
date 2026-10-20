/* asm/cod/026920.s -> execute_cfa_insn.
 * GCC frame.c/frame-dwarf2.c execute_cfa_insn (authentic source), the revision
 * with DW_CFA_def_cfa_expression (decode_stack_op = 026800) and the
 * cfa_reg skip in DW_CFA_offset/offset_extended.
 * MATCHED. */
#include "frame2000.h"

enum dwarf_call_frame_info
  {
    DW_CFA_advance_loc = 0x40,
    DW_CFA_offset = 0x80,
    DW_CFA_restore = 0xc0,
    DW_CFA_nop = 0x00,
    DW_CFA_set_loc = 0x01,
    DW_CFA_advance_loc1 = 0x02,
    DW_CFA_advance_loc2 = 0x03,
    DW_CFA_advance_loc4 = 0x04,
    DW_CFA_offset_extended = 0x05,
    DW_CFA_restore_extended = 0x06,
    DW_CFA_undefined = 0x07,
    DW_CFA_same_value = 0x08,
    DW_CFA_register = 0x09,
    DW_CFA_remember_state = 0x0a,
    DW_CFA_restore_state = 0x0b,
    DW_CFA_def_cfa = 0x0c,
    DW_CFA_def_cfa_register = 0x0d,
    DW_CFA_def_cfa_offset = 0x0e,
    DW_CFA_def_cfa_expression = 0x0f,
    /* SGI/MIPS specific */
    DW_CFA_MIPS_advance_loc8 = 0x1d,

    /* GNU extensions */
    DW_CFA_GNU_window_save = 0x2d,
    DW_CFA_GNU_args_size = 0x2e,
    DW_CFA_GNU_negative_offset_extended = 0x2f
  };

#define decode_stack_op func_00126800
void *decode_stack_op (unsigned char *buf, struct frame_state *state);

void *
execute_cfa_insn (void *p, struct frame_state_internal *state,
		  struct cie_info *info, void **pc)
{
  unsigned insn = *(unsigned char *)p++;
  unsigned reg;
  int offset;

  if (insn & DW_CFA_advance_loc)
    *pc += ((insn & 0x3f) * info->code_align);
  else if (insn & DW_CFA_offset)
    {
      reg = (insn & 0x3f);
      p = decode_uleb128 (p, &offset);
      if (reg == state->s.cfa_reg)
	/* Don't record anything about this register; it's only used to
	   reload SP in the epilogue.  We don't want to copy in SP
	   values for outer frames; we handle restoring SP specially.  */;
      else
	{
	  offset *= info->data_align;
	  state->s.saved[reg] = REG_SAVED_OFFSET;
	  state->s.reg_or_offset[reg] = offset;
	}
    }
  else if (insn & DW_CFA_restore)
    {
      reg = (insn & 0x3f);
      state->s.saved[reg] = REG_UNSAVED;
    }
  else switch (insn)
    {
    case DW_CFA_set_loc:
      *pc = read_pointer (p);
      p += sizeof (void *);
      break;
    case DW_CFA_advance_loc1:
      *pc += read_1byte (p);
      p += 1;
      break;
    case DW_CFA_advance_loc2:
      *pc += read_2byte (p);
      p += 2;
      break;
    case DW_CFA_advance_loc4:
      *pc += read_4byte (p);
      p += 4;
      break;

    case DW_CFA_offset_extended:
      p = decode_uleb128 (p, &reg);
      p = decode_uleb128 (p, &offset);
      if (reg == state->s.cfa_reg)
	/* Don't record anything; see above.  */;
      else
	{
	  offset *= info->data_align;
	  state->s.saved[reg] = REG_SAVED_OFFSET;
	  state->s.reg_or_offset[reg] = offset;
	}
      break;
    case DW_CFA_restore_extended:
      p = decode_uleb128 (p, &reg);
      state->s.saved[reg] = REG_UNSAVED;
      break;

    case DW_CFA_undefined:
    case DW_CFA_same_value:
    case DW_CFA_nop:
      break;

    case DW_CFA_register:
      {
	unsigned reg2;
	p = decode_uleb128 (p, &reg);
	p = decode_uleb128 (p, &reg2);
	state->s.saved[reg] = REG_SAVED_REG;
	state->s.reg_or_offset[reg] = reg2;
      }
      break;

    case DW_CFA_def_cfa:
      p = decode_uleb128 (p, &reg);
      p = decode_uleb128 (p, &offset);
      state->s.cfa_reg = reg;
      state->s.cfa_offset = offset;
      break;
    case DW_CFA_def_cfa_register:
      p = decode_uleb128 (p, &reg);
      state->s.cfa_reg = reg;
      break;
    case DW_CFA_def_cfa_offset:
      p = decode_uleb128 (p, &offset);
      state->s.cfa_offset = offset;
      break;
    case DW_CFA_def_cfa_expression:
      {
	void *end;
	state->s.cfa_reg = 0;
	state->s.cfa_offset = 0;
	state->s.base_offset = 0;
	state->s.indirect = 0;

	p = decode_uleb128 (p, &offset);
	end = p + offset;
	while (p < end)
	  p = decode_stack_op (p, &(state->s));
	break;
      }

    case DW_CFA_remember_state:
      {
	struct frame_state_internal *save =
	  (struct frame_state_internal *)
	  malloc (sizeof (struct frame_state_internal));
	/* the image expands this copy inline: the builtin, not the libc memcpy */
	__builtin_memcpy (save, state, sizeof (struct frame_state_internal));
	state->saved_state = save;
      }
      break;
    case DW_CFA_restore_state:
      {
	struct frame_state_internal *save = state->saved_state;
	__builtin_memcpy (state, save, sizeof (struct frame_state_internal));
	free (save);
      }
      break;

      /* FIXME: Hardcoded for SPARC register window configuration.  */
    case DW_CFA_GNU_window_save:
      for (reg = 16; reg < 32; ++reg)
	{
	  state->s.saved[reg] = REG_SAVED_OFFSET;
	  state->s.reg_or_offset[reg] = (reg - 16) * sizeof (void *);
	}
      break;

    case DW_CFA_GNU_args_size:
      p = decode_uleb128 (p, &offset);
      state->s.args_size = offset;
      break;

    case DW_CFA_GNU_negative_offset_extended:
      p = decode_uleb128 (p, &reg);
      p = decode_uleb128 (p, &offset);
      offset *= info->data_align;
      state->s.saved[reg] = REG_SAVED_OFFSET;
      state->s.reg_or_offset[reg] = -offset;
      break;

    default:
      abort ();
    }
  return p;
}
