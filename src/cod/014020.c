/* asm/cod/014020.s -> func_00114020 @ 0x00114020 (0x5C bytes)
 *   sll   $a1, $a1, 16
 *   sra   $a1, $a1, 16                 ; (short)a1
 *   dsll32/dsra32 $a1, 16              ; (long long)(short)a1
 *   ... 64-bit constants in registers ...
 *   sd    $a5, 0x8($a0)                ; p[1] = 0x42
 *   sd    $v1, 0x0($a0)                ; p[0] = 0x44
 *   sd    $v0, 0x18($a0)               ; p[3] = 0x49
 *   sd    $a1, 0x10($a0)               ; p[2] = (short)a1
 *   sd    $a2, 0x28($a0)               ; p[5] = 0x3B
 *   sd    $a3, 0x20($a0)               ; p[4] = 0x000000810000807F
 *   sd    $a4, 0x38($a0)               ; p[7] = 0x4A
 *   sd    $zero, 0x30($a0)             ; p[6] = 0
 *   sync
 *   jr    $ra
 *    addiu $v0, $zero, 0x4
 *
 * Build a small transfer list of 64-bit words (DMA/GS packet fragment) and
 * fence with `sync`. Constant roles UNCONFIRMED.
 */
int func_00114020(long long *p, short a1) {
    p[1] = 0x42;
    p[0] = 0x44;
    p[3] = 0x49;
    p[2] = a1;
    p[5] = 0x3B;
    p[4] = 0x000000810000807FLL;
    p[7] = 0x4A;
    p[6] = 0;
    __asm__ __volatile__("sync" ::: "memory");
    return 4;
}
