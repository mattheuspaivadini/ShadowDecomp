/* asm/cod/022448.s -> func_00122448 @ 0x00122448 (0x10 bytes)
 *   lui   $v1, %hi(D_00135958)
 *   daddu $v0, $zero, $zero
 *   jr    $ra
 *    sw   $a0, %lo(D_00135958)($v1)
 */
#include "symbols.h"

int sceNetcnfifSetFNoDecode(int value) {
    D_00135958 = value;
    return 0;
}
