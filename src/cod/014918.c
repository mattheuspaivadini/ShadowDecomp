/* Phase 3 flag-pinning case: bounds-checked table lookup.
 * asm/cod/014918.s -> func_00114918 @ 0x00114918 (0x28 bytes)
 *   sltiu $v0, $a0, 0xA
 *   beqz  $v0, .L00114938
 *    lui  $v0, %hi(D_001339B0)
 *   sll   $v1, $a0, 2
 *   addiu $v0, $v0, %lo(D_001339B0)
 *   addu  $v1, $v1, $v0
 *   jr    $ra
 *    lw   $v0, 0x0($v1)
 * .L00114938:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * D_001339B0 is in .data (outside the gp window): 10 ints = 40 bytes, i.e.
 * not a small-data object, which is why the access is absolute.
 */
extern int D_001339B0[];

int func_00114918(unsigned int idx) {
    if (idx < 10u) {
        return D_001339B0[idx];
    }
    return 0;
}
