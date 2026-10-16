/* asm/cod/006B58.s -> func_00106B58 @ 0x00106B58 (0x34 bytes)
 *   lw    $v0, %gp_rel(D_0013A170)($gp)   ; row
 *   lw    $a2, %gp_rel(D_0013A16C)($gp)   ; col
 *   sll   $v1, $v0, 4
 *   subu  $v1, $v1, $v0                   ; row * 15
 *   sll   $v1, $v1, 2                     ; row * 60
 *   addu  $v1, $v1, $a2                   ; + col
 *   sll   $v1, $v1, 3                     ; * 8 bytes/element
 *   lui   $at, %hi(D_0013ED90)
 *   addiu $at, $at, %lo(D_0013ED90)
 *   addu  $v1, $at, $v1
 *   sb    $a1, 0x4($v1)                   ; field04 = (byte)arg1
 *   jr    $ra
 *    sw   $a0, 0x0($v1)                   ; field00 = arg0
 *
 * Store two fields in the 8-byte record of a 60-column table:
 * row = D_0013A170, col = D_0013A16C (both gp-relative .sdata/.sbss).
 */
#include "symbols.h"

struct E006B58 {
    int           field00;   /* 0x00 */
    unsigned char field04;   /* 0x04 */
    char          pad05[3];
};

extern struct E006B58 D_0013ED90[];

void PutChar(int a0, unsigned char a1) {
    int idx = D_0013A170 * 60 + D_0013A16C;

    D_0013ED90[idx].field00 = a0;
    D_0013ED90[idx].field04 = a1;
}
