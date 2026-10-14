/* asm/cod/0029C8.s -> func_001029C8 @ 0x001029C8 (0x34 bytes)
 *   lui   $v0, %hi(D_0013BF90)
 *   addiu $a0, $zero, -0x1
 *   addiu $v0, $v0, %lo(D_0013BF90)
 *   addiu $v1, $zero, 0xFF
 * .L001029D8:
 *   addiu $v1, $v1, -0x1
 *   sw    $a0, 0x4($v0)
 *   sw    $a0, 0x0($v0)
 *   nop
 *   nop
 *   bgez  $v1, .L001029D8
 *    addiu $v0, $v0, 0x8
 *   jr    $ra
 *    nop
 *
 * Clears 256 pairs of words (2 KB) to -1 starting at D_0013BF90 (.bss).
 * STATUS (2026-10-14): NON_MATCHING - the original has two `nop`s inside the
 * loop body (the known EE-GCC "nop around short loop" quirk, also documented by
 * Fantaskink/SOTC); our build emits the 5-instruction body without them.
 */
#include "symbols.h"

void func_001029C8(void) {
    int *p = D_0013BF90;
    int i;

    for (i = 0xFF; i >= 0; i--) {
        p[1] = -1;
        p[0] = -1;
        p += 2;
    }
}
