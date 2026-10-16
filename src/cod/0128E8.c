/* MATCHING (Session 4, 2026-10-14): byte-exact only with the ALTERNATE EE-GCC
 * revision `ee-gcc2.9-991111-01` (manifest token `cc=29`); see 0128D0.c.
 * Evidence: tools/cc_matrix.py, docs/compiler.md section 4.3.
 *
 * asm/cod/0128E8.s -> func_001128E8 @ 0x001128E8 (0x18 bytes)
 *   lui   $v0, %hi(D_0014B500)
 *   sll   $a0, $a0, 2
 *   addiu $v0, $v0, %lo(D_0014B500)
 *   addu  $a0, $a0, $v0
 *   daddu $v0, $a1, $zero
 *   jr    $ra
 *    sw   $a1, 0x0($a0)
 */
#include "symbols.h"

int sceSifSetSreg(int index, int value) {
    D_0014B500[index] = value;
    return value;
}
