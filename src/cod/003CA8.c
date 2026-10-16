/* asm/cod/003CA8.s -> func_00103CA8 @ 0x00103CA8 (0x10 bytes)
 *   lui   $v0, %hi(D_0013CF90)
 *   jr    $ra
 *    addiu $v0, $v0, %lo(D_0013CF90)
 *
 * D_0013CF90 is in .bss, i.e. outside the gp window, so the address is built
 * absolutely - it returns the address, not the contents.
 */
#include "symbols.h"

void *LoaderSysGetBootArg(void) {
    return D_0013CF90;
}
