/* asm/cod/027528.s -> func_00127528 @ 0x00127528 (0x10 bytes)
 *   lui   $v1, %hi(D_00135C60)
 *   jr    $ra
 *    lw   $v0, %lo(D_00135C60)($v1)
 */
#include "symbols.h"

int func_00127528(void) {
    return D_00135C60;
}
