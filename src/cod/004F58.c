/* asm/cod/004F58.s -> func_00104F58 @ 0x00104F58 (0x8 bytes)
 *   jr   $ra
 *    sw  $a0, %gp_rel(D_0013A11C)($gp)
 *
 * The stored value's type is only known from the access width (32-bit int).
 */
#include "symbols.h"

void func_00104F58(int value) {
    D_0013A11C = value;
}
