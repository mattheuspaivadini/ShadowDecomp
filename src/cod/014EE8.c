/* MATCHED (Session 5, step 2). Evidence: tools/permute.py ->
 * build/permute/014EE8 (v01_unsigned_p, cc=29, score 0).
 *
 * asm/cod/014EE8.s -> func_00114EE8 @ 0x00114EE8 (0x38 bytes)
 *   addiu $sp, $sp, -0x10
 *   addiu $v0, $zero, 0x1
 *   bne   $a1, $v0, .L00114F08
 *    sd   $ra, 0x0($sp)
 *   lw    $v0, 0x0($a0)
 *   srl   $v0, $v0, 8            ; LOGICAL shift -> unsigned field
 *   b     .L00114F14
 *    andi $v0, $v0, 0x1
 * .L00114F08:
 *   jal   func_001147C0
 *    nop
 *   daddu $v0, $zero, $zero
 * .L00114F14:
 *   ld    $ra, 0x0($sp)
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 *
 * Matching note: the field must be `unsigned` — a signed `int` reproduces the
 * `sra` (1 instruction off).
 */
int func_001147C0(unsigned *p);

int func_00114EE8(unsigned *p, int a1) {
    if (a1 == 1)
        return (*p >> 8) & 1;
    func_001147C0(p);
    return 0;
}
