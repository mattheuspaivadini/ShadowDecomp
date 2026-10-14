/* asm/cod/010640.s -> func_00110640 @ 0x00110640 (0x2C bytes)
 *   lui   $v0, %hi(D_00133920)
 *   lw    $v1, %lo(D_00133920)($v0)
 *   bgez  $v1, .L0011065C
 *    lui  $v1, (0x10001010 >> 16)        <- branch delay slot
 *   lui   $v0, (0x80008001 >> 16)
 *   jr    $ra
 *    ori  $v0, $v0, (0x80008001 & 0xFFFF)
 * .L0011065C:
 *   ori   $v1, $v1, (0x10001010 & 0xFFFF)
 *   lw    $v0, 0x0($v1)
 *   jr    $ra
 *    andi $v0, $v0, 0x3
 *
 * D_00133920 is in .data, i.e. outside the gp window -> absolute addressing.
 * 0x10001010 is an EE hardware register; 0x80008001 is an error sentinel.
 */
#include "symbols.h"

int func_00110640(void) {
    if (D_00133920 < 0) {
        return 0x80008001;
    }
    return HWREG(0x10001010) & 3;
}
