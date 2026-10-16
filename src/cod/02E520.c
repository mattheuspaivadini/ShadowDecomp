/* asm/cod/02E520.s -> func_0012E520 @ 0x0012E520 (0x10 bytes)
 *   lui   $v0, %hi(D_00139B08)
 *   jr    $ra
 *    addiu $v0, $v0, %lo(D_00139B08)
 */
#include "symbols.h"

void *_localeconv_r(void) {
    return D_00139B08;
}
