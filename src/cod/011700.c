/* asm/cod/011700.s -> func_00111700 @ 0x00111700 (0x4C bytes)
 *   lui   $a1, %hi(D_0014A880)
 *   lui   $v1, %hi(D_0014AC80)
 *   addiu $v0, $a1, %lo(D_0014A880)   ; base
 *   addiu $a0, $zero, 0x3F
 *   sw    $v0, %lo(D_0014AC80)($v1)   ; D_0014AC80 = base
 *   addiu $v1, $v0, 0x400             ; q = base + 0x400
 *   addiu $v0, $v0, 0x3F0             ; p = base + 0x3F0
 * .L00111720:
 *   sw    $v1, 0x0($v0)               ; *p = q
 *   addiu $a0, $a0, -0x1
 *   addiu $v0, $v0, -0x10             ; p -= 0x10
 *   addiu $v1, $v1, -0x10             ; q -= 0x10
 *   bgez  $a0, .L00111720
 *    nop
 *   addiu $v1, $a1, %lo(D_0014A880)
 *   daddu $v0, $zero, $zero
 *   jr    $ra
 *    sw   $zero, 0x3F0($v1)           ; base[0x3F0/4] = 0
 *
 * Build a 64-node free list of 0x10-byte records inside D_0014A880, each
 * pointing at the next (record k -> record k+1); terminate the head at 0 and
 * publish the base in D_0014AC80.
 */
extern char D_0014A880[];
extern void *D_0014AC80[];   /* pointer variable in .data */

int func_00111700(void) {
    char *base = D_0014A880;
    char *p;
    char *q;
    int i;

    D_0014AC80[0] = base;
    p = base + 0x3F0;
    q = base + 0x400;
    for (i = 0x3F; i >= 0; i--) {
        *(char **)p = q;
        p -= 0x10;
        q -= 0x10;
    }
    *(int *)(base + 0x3F0) = 0;
    return 0;
}
