/* asm/cod/014C30.s -> func_00114C30 @ 0x00114C30 (0x14 bytes)
 *   lui   $v1, (0x1000E060 >> 16)
 *   ori   $v1, $v1, (0x1000E060 & 0xFFFF)
 *   lw    $v0, 0x0($v1)
 *   jr    $ra
 *    sw   $a0, 0x0($v1)
 *
 * A read-modify-write of one EE hardware register, i.e. a volatile access that
 * returns the previous value.
 * UNCONFIRMED: what 0x1000E060 is (EE DMAC/SIF register block); the access
 * width (32-bit) is evidenced by the lw/sw pair.
 */
#include "symbols.h"

unsigned int func_00114C30(unsigned int value) {
    unsigned int old = HWREG(0x1000E060);
    HWREG(0x1000E060) = value;
    return old;
}
