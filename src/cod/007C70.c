/* asm/cod/007C70.s -> func_00107C70 @ 0x00107C70 (0x38 bytes)
 *   lui   $v1, 0x1000F130
 *   ori   $v1, $v1, 0xF130
 * .L00107C78:
 *   lw    $v0, 0x0($v1)
 *   andi  $v0, $v0, 0x8000
 *   nop x3
 *   bnez  $v0, .L00107C78
 *    nop
 *   lui   $v1, 0x1000F180
 *   daddu $v0, $a0, $zero        ; return value
 *   ori   $v1, $v1, 0xF180
 *   jr    $ra
 *    sb   $a0, 0x0($v1)
 *
 * Poll the status register 0x1000F130 (bit 0x8000) until clear, then write the
 * byte to 0x1000F180 and return it. Both are unconfirmed EE register
 * identifications (docs/structs.md).
 */
int func_00107C70(unsigned int value) {
    while (*(volatile unsigned int *)0x1000F130 & 0x8000)
        ;
    *(volatile unsigned char *)0x1000F180 = value;
    return value;
}
