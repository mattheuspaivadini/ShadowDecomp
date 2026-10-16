/* asm/cod/001A48.s -> func_00101A48 @ 0x00101A48 (0x8 bytes)
 *   jr   $ra
 *    lw  $v0, %gp_rel(D_00139E04)($gp)
 */
#include "symbols.h"

int GetHeapCurrentPoint(void) {
    return D_00139E04;
}
