/* asm/cod/020438.s -> func_00120438 @ 0x00120438 (0x34 bytes)
 *   lui   $v0, %hi(D_0015F480)
 *   addiu $a1, $zero, -0x1             ; fill value -1
 *   addiu $v1, $v0, %lo(D_0015F480)    ; p = D_0015F480
 *   addiu $a0, $v1, 0x4020             ; end = p + 0x4020
 * .L00120448:
 *   sw    $a1, 0x0($v1)
 *   sw    $zero, 0xC($v1)
 *   addiu $v1, $v1, 0x2010             ; p += 0x2010
 *   slt   $v0, $v1, $a0
 *   bnez  $v0, .L00120448
 *    nop
 *   jr    $ra
 *    addiu $v0, $zero, 0x1             ; return 1
 *
 * Initialise two records of 0x2010 bytes each at D_0015F480: field00 = -1,
 * field0C = 0. The loop bound is the pointer D+0x4020.
 */
extern char D_0015F480[];

int _sceMcpInit(void) {
    char *p = D_0015F480;
    char *end = D_0015F480 + 0x4020;

    do {
        *(int *)(p + 0x00) = -1;
        *(int *)(p + 0x0C) = 0;
        p += 0x2010;
    } while ((int)p < (int)end);
    return 1;
}
