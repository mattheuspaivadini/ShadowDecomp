/* Phase 3 flag-pinning case (gp-relative store -> pins -G / -mgpopt).
 * asm/cod/001A30.s -> func_00101A30 @ 0x00101A30 (0x14 bytes)
 *   addiu $a0, $a0, 0xF
 *   addiu $v0, $zero, -0x10
 *   and   $a0, $a0, $v0
 *   jr    $ra
 *    sw   $a0, %gp_rel(D_00139E04)($gp)
 */
#include "symbols.h"

void SetHeapStartPoint(int size) {
    D_00139E04 = (size + 15) & ~15;
}
