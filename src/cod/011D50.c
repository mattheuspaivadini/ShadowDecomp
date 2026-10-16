/* Phase 3 flag-pinning case (absolute addressing of a non-small global).
 * asm/cod/011D50.s -> func_00111D50 @ 0x00111D50 (0x10 bytes, last word padding)
 *   lui  $v0, %hi(D_00133940)
 *   jr   $ra
 *    sw  $zero, %lo(D_00133940)($v0)
 */
#include "symbols.h"

void sceResetttyinit(void) {
    D_00133940 = 0;
}
