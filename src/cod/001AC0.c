/* asm/cod/001AC0.s -> func_00101AC0 @ 0x00101AC0 (0x2C bytes, 11 insns)
 *   lw    $v0, %gp_rel(D_00139E04)($gp)   ; v0 = D (bump pointer, .sdata)
 *   beql  $a1, $zero, .L00101ACC          ; a1 == 0 -> the delay slot traps
 *    break 0, 7                           ; (division-by-zero check)
 * .L00101ACC:
 *   addu  $v0, $v0, $a1
 *   addiu $v0, $v0, -0x1
 *   divu  $zero, $v0, $a1                 ; unsigned division
 *   mflo  $v0
 *   mult  $v0, $v0, $a1                   ; R5900 3-operand mult (2.9 shape)
 *   addu  $a0, $v0, $a0                   ; $a0 = aligned base + size
 *   jr    $ra
 *    sw   $a0, %gp_rel(D_00139E04)($gp)   ; D = aligned base + size
 *
 * Bump the global pointer: align the current value up to `align` (a1), add
 * `size` (a0), store that back and return the aligned base (the value left in
 * $v0 by the `mult` at the `jr`).
 *
 * Registered next to func_00101AF0 (fixed 0x100 alignment) in the table built
 * by func_00100D48, so the `divide/multiply by a runtime alignment` shape is
 * the allocator family. The `divu` (not `div`) fixes the unsigned types, the
 * `mult $v0,$v0,$a1` is the 2.9 generation shape.
 * MATCH GUESS: cc=29 */
#include "symbols.h"

unsigned int func_00101AC0(unsigned int size, unsigned int align) {
    unsigned int base = ((unsigned int)D_00139E04 + align - 1) / align * align;

    D_00139E04 = base + size;
    return base;
}
