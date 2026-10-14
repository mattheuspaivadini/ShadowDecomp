/* asm/cod/001AF0.s -> func_00101AF0 @ 0x00101AF0 (0x2C bytes, 11 insns)
 *
 * Bump-pointer helper for D_00139E04 (the .sdata allocator cursor used by the
 * matched 001A30/001A48/001AC0) with a FIXED 0x100 alignment:
 *
 *   lw    $v0, %gp_rel(D_00139E04)($gp)   ; v0 = D
 *   addiu $v1, $zero, 0x100               ; align, kept in a register
 *   beql  $v1, $zero, .L00101B00          ; division-by-zero guard is LIVE
 *    break 0, 7                           ; -> the divisor was not a folded const
 *   addiu $v0, $v0, 0xFF                  ; D + align - 1 (folded)
 *   divu  $zero, $v0, $v1                 ; unsigned divide (not `srl`)
 *   mflo  $v0
 *   sll   $v0, $v0, 8                     ; * align  -> shift (combine folded it)
 *   addu  $a0, $v0, $a0                   ; aligned base + size
 *   jr    $ra
 *    sw   $a0, %gp_rel(D_00139E04)($gp)   ; D = aligned base + size
 *
 * Same body as the matched func_00101AC0 (there the alignment arrives as a
 * parameter, hence `mult`); here it is a local initialised to 0x100. That a
 * local survives as a register at *expand* time is what keeps the guard alive
 * and the division a `divu` while the multiply still collapses to a shift - the
 * image shows the identical asymmetry at the 0x10-alignment site in
 * asm/cod/001D90.s (`addiu $a0,$zero,0x10` ... `divu` ... `sll $v0,$v0,4`).
 *
 * Return value = the aligned base (the value left in $v0 by the shift), which
 * is not the value stored into D_00139E04.
 * MATCH GUESS: cc=29 (same allocator family as the matched func_00101AC0)
 */
#include "symbols.h"

unsigned int func_00101AF0(unsigned int size) {
    unsigned int align = 0x100;
    unsigned int base = ((unsigned int)D_00139E04 + align - 1) / align * align;

    D_00139E04 = base + size;
    return base;
}
