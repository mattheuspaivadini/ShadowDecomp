/* asm/cod/006380.s -> func_00106380 @ 0x00106380 (0x10 bytes)
 *   sw   $a0, %gp_rel(D_0013A16C)($gp)
 *   jr   $ra
 *    sw  $a1, %gp_rel(D_0013A170)($gp)
 */
#include "symbols.h"

void SetLocate(int a, int b) {
    D_0013A16C = a;
    D_0013A170 = b;
}
