/* asm/cod/011C50.s -> func_00111C50 @ 0x00111C50 (0x54 bytes)
 *   bgezl $a0, .L00111C74
 *    lui  $v0, %hi(D_00133938)
 *   lui   $v0, (0x7FFFFFFF >> 16)
 *   lui   $v1, %hi(D_0014AC88)
 *   ori   $v0, $v0, (0x7FFFFFFF & 0xFFFF)
 *   addiu $a1, $v1, %lo(D_0014AC88)
 *   and   $a0, $a0, $v0
 *   b     .L00111C80
 *    addiu $v0, $zero, 0x20
 * .L00111C74:
 *   lui   $v1, %hi(D_0013393C)
 *   lw    $a1, %lo(D_00133938)($v0)
 *   lw    $v0, %lo(D_0013393C)($v1)
 * .L00111C80:
 *   sltu  $v0, $a0, $v0
 *   bnez  $v0, .L00111C94
 *    sll  $v1, $a0, 4
 *   jr    $ra
 *    addiu $v0, $zero, -0x69
 * .L00111C94:
 *   daddu $v0, $zero, $zero
 *   addu  $v1, $v1, $a1
 *   jr    $ra
 *    sw   $zero, 0x0($v1)              ; base[idx*16] = 0
 *
 * Bounds-checked record clear: for a negative index use the fallback table
 * (D_0014AC88, 0x20 records) and clear the sign bit; else use the table at
 * D_00133938 with its count at D_0013393C. Returns 0, or -0x69 out of range.
 */
extern void *D_00133938[];   /* array => non-small (absolute addressing) */
extern int D_0013393C[];
extern char D_0014AC88[];

int func_00111C50(int index) {
    void *base;
    unsigned int count;

    if (index >= 0) {
        base = D_00133938[0];
        count = D_0013393C[0];
    } else {
        base = D_0014AC88;
        count = 0x20;
        index &= 0x7FFFFFFF;
    }
    if ((unsigned int)index >= count)
        return -0x69;
    *(int *)((char *)base + index * 16) = 0;
    return 0;
}
