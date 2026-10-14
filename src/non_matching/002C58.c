/* asm/cod/002C58.s -> func_00102C58 @ 0x00102C58 (0x38 bytes)
 *   lui   $v0, %hi(D_0013C790)
 *   addiu $v1, $zero, 0xFF
 *   addiu $v0, $v0, %lo(D_0013C790)
 *   addiu $v0, $v0, 0x3FC
 * .L00102C68:
 *   addiu $v1, $v1, -0x1
 *   sw    $zero, 0x0($v0)
 *   nop
 *   nop
 *   nop
 *   bgez  $v1, .L00102C68
 *    addiu $v0, $v0, -0x4
 *   jr    $ra
 *    nop
 *
 * Clears 256 words (1 KB) to 0, walking *downwards* from D_0013C790 + 0x3FC.
 * STATUS (2026-10-14): NON_MATCHING - same "nop around short loop" quirk as
 * func_001029C8 (three `nop`s in the original's loop body).
 */
#include "symbols.h"

void func_00102C58(void) {
    int *p = D_0013C790 + 0xFF;
    int i;

    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}
