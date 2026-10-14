/* asm/cod/0128D0.s -> func_001128D0 @ 0x001128D0 (0x14 bytes)
 *   lui   $v0, %hi(D_0014B500)
 *   sll   $a0, $a0, 2
 *   addiu $v0, $v0, %lo(D_0014B500)
 *   addu  $a0, $a0, $v0
 *   jr    $ra
 *    lw   $v0, 0x0($a0)
 */
#include "symbols.h"

int func_001128D0(int index) {
    return D_0014B500[index];
}
