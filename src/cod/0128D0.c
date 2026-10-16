/* MATCHING (Session 4, 2026-10-14): byte-exact only with the ALTERNATE EE-GCC
 * revision `ee-gcc2.9-991111-01` (manifest token `cc=29`); it emits the split
 * `lui`/`addiu` base plus a separate `%lo` memory operand, while 2.96 folds
 * `%lo` into the load. Evidence: tools/cc_matrix.py, docs/compiler.md 4.3.
 *
 * asm/cod/0128D0.s -> func_001128D0 @ 0x001128D0 (0x14 bytes)
 *   lui   $v0, %hi(D_0014B500)
 *   sll   $a0, $a0, 2
 *   addiu $v0, $v0, %lo(D_0014B500)
 *   addu  $a0, $a0, $v0
 *   jr    $ra
 *    lw   $v0, 0x0($a0)
 */
#include "symbols.h"

int sceSifGetSreg(int index) {
    return D_0014B500[index];
}
