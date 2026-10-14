/* asm/cod/02E6D0.s -> func_00102E6D0 @ 0x00102E6D0 (0x34 bytes)
 *   addiu $sp, $sp, -0x10
 *   daddu $v0, $zero, $zero            ; result = 0
 *   daddu $v1, $sp, $zero              ; p = &local
 *   beqz  $a2, .Lend
 *    movn $v1, $a1, $a1                ; if (a1) p = a1
 *   beqz  $a3, .Lend
 *    addiu $v0, $zero, -0x1             ; result = -1
 *   lbu   $v0, 0x0($a2)
 *   sw    $v0, 0x0($v1)                ; *p = *a2
 *   lbu   $v0, 0x0($a2)
 *   sltu  $v0, $zero, $v0              ; return *a2 != 0
 * .Lend:
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 *
 * `a0` is unused by the body; semantics UNCONFIRMED (looks like a guarded
 * get-or-store with a local fallback).
 */
int func_0012E6D0(int unused, int *dst, unsigned char *src, int flag) {
    int local;
    int *p = dst ? dst : &local;

    if (src == 0)
        return 0;
    if (flag == 0)
        return -1;
    *p = *src;
    return *src != 0;
}
