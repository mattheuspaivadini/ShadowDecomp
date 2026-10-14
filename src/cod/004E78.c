/* Phase 3 flag-pinning case: constant-multiply strength reduction.
 * asm/cod/004E78.s -> func_00104E78 @ 0x00104E78 (0x20 bytes, last word padding)
 *   sll   $v0, $a0, 2          ; x * 4
 *   addu  $v0, $v0, $a0        ; + x   -> 5x
 *   sll   $v0, $v0, 6          ; << 6  -> 320x
 *   lui   $at, %hi(D_0013D840)
 *   addiu $at, $at, %lo(D_0013D840)
 *   addu  $v0, $at, $v0
 *   jr    $ra
 *    nop
 *
 * D_0013D840 lives in .bss (outside the gp window) and the elements are
 * 320 bytes, so this pins both the strength-reduction sequence and the
 * non-small-data addressing.
 */
extern char D_0013D840[];

char *func_00104E78(int x) {
    return &D_0013D840[x * 320];
}
