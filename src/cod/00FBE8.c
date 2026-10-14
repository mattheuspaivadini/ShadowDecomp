/* asm/cod/00FBE8.s -> func_0010FBE8 @ 0x0010FBE8 (0x10 bytes)
 *   lui   $v1, %hi(D_001329A4)
 *   jr    $ra
 *    lw   $v0, %lo(D_001329A4)($v1)
 */
#include "symbols.h"

int func_0010FBE8(void) {
    return D_001329A4;
}
