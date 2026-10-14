/* asm/cod/012C78.s -> func_00112C78 @ 0x00112C78 (0x4C bytes)
 *   daddu $a2, $a0, $zero
 *   bgez  $a2, .L00112CAC
 *    addiu $v0, $zero, 0xC
 *   lui   $v0, (0x7FFFFFFF >> 16)
 *   addiu $a1, $zero, 0xC
 *   ori   $v0, $v0, (0x7FFFFFFF & 0xFFFF)
 *   lui   $v1, %hi(D_0014B364)
 *   and   $v0, $a2, $v0
 *   lw    $a0, %lo(D_0014B364)($v1)
 *   mult  $v0, $v0, $a1                ; index * 0xC
 *   addu  $v0, $v0, $a0
 *   jr    $ra
 *    sw   $zero, 0x0($v0)
 * .L00112CAC:
 *   lui   $a0, %hi(D_0014B36C)
 *   mult  $v0, $a2, $v0                ; index * 0xC
 *   lw    $v1, %lo(D_0014B36C)($a0)
 *   addu  $v0, $v0, $v1
 *   jr    $ra
 *    sw   $zero, 0x0($v0)
 *
 * Clear the first word of the `index`-th 0xC-byte record of one of two tables.
 * A negative index has its sign bit masked and selects D_0014B364; a
 * non-negative one selects D_0014B36C. Both globals hold a pointer.
 */
extern char *D_0014B364[];
extern char *D_0014B36C[];

void func_00112C78(int index) {
    char *base;

    if (index < 0) {
        index &= 0x7FFFFFFF;
        base = D_0014B364[0];
    } else {
        base = D_0014B36C[0];
    }
    *(int *)(base + index * 0xC) = 0;
}
