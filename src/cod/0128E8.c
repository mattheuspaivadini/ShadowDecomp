/* asm/cod/0128E8.s -> func_001128E8 @ 0x001128E8 (0x18 bytes)
 *   lui   $v0, %hi(D_0014B500)
 *   sll   $a0, $a0, 2
 *   addiu $v0, $v0, %lo(D_0014B500)
 *   addu  $a0, $a0, $v0
 *   daddu $v0, $a1, $zero
 *   jr    $ra
 *    sw   $a1, 0x0($a0)
 */
#include "symbols.h"

int func_001128E8(int index, int value) {
    D_0014B500[index] = value;
    return value;
}
