/* asm/cod/013520.s -> func_00113520 @ 0x00113520 (0x10 bytes)
 *   lui   $v0, %hi(D_00133970)
 *   jr    $ra
 *    addiu $v0, $v0, %lo(D_00133970)
 */
#include "symbols.h"

void *func_00113520(void) {
    return &D_00133970;
}
