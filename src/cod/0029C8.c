/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/0029C8/batch1.json (v01_value_before_p, cc=296, score 0).
 *
 * asm/cod/0029C8.s -> func_001029C8 @ 0x001029C8 (0x34 bytes)
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
 *
 * Matching notes:
 * - the two `nop`s inside the loop body are the EE-GCC "short loop" padding
 *   (also documented by Fantaskink/SOTC) and DO appear for this source shape;
 * - the `-1` must be a *local initialised before the loop* (`int value = -1;`)
 *   so LICM hoists it into `$a0` before the counter reaches `$v1`; the plain
 *   literal gets the opposite register roles (score 6);
 * - cc=296 only (cc=29 best score 4).
 */
#include "symbols.h"

void LoaderSysInitExternalIntcHandlerList(void) {
    int value = -1;
    int *p = (int *)D_0013BF90;
    int i;

    for (i = 0xFF; i >= 0; i--) {
        p[1] = value;
        p[0] = value;
        p += 2;
    }
}
