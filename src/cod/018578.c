/* MATCHED (Session 5, step 2). Evidence: tools/permute.py ->
 * build/permute/018578 (v01_early_return, cc=29, score 0).
 *
 * asm/cod/018578.s -> func_00118578 @ 0x00118578 (0x2C bytes)
 *   addiu $sp, $sp, -0x10
 *   daddu $v0, $a1, $zero
 *   beqz  $a0, .L00118594
 *    sd   $ra, 0x0($sp)
 *   sll   $a1, $a2, 2
 *   jal   func_00128FB0
 *    addu $a1, $v0, $a1
 * .L00118594:
 *   daddu $v0, $zero, $zero       ; set before the epilogue
 *   ld    $ra, 0x0($sp)
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 *
 * Matching note: the early `return 0` (not a merged tail return) keeps
 * `daddu $v0,$zero,$zero` before `ld $ra`; the merged form transposes them.
 */
int func_00128FB0(int a0, int *p);

int func_00118578(int a0, int *a1, int a2) {
    if (a0 == 0)
        return 0;
    func_00128FB0(a0, &a1[a2]);
    return 0;
}
