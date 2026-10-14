/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/002C58/batch1.json (v04_step_in_body, cc=296, score 0).
 *
 * asm/cod/002C58.s -> func_00102C58 @ 0x00102C58 (0x38 bytes)
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
 *
 * Matching notes:
 * - the pointer must be built as `(int *)D_0013C790` (a char array in
 *   symbols.h) and advanced with a separate `p += 0xFF`, so the original's
 *   two-instruction address materialisation (`%lo` then `+0x3FC`) appears;
 *   folding the offset into the initialiser (`(int *)D + 0xFF` or
 *   `(int *)(D + 0x3FC)`) puts 0x3FC into the %lo addend and fails;
 * - the three `nop`s inside the loop body are the EE-GCC "short loop" padding
 *   and appear with cc=296 for this source shape (score 0);
 * - cc=29 does *not* reproduce it (best score 4).
 */
#include "symbols.h"

void func_00102C58(void) {
    int *p = (int *)D_0013C790;
    int i;

    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}
