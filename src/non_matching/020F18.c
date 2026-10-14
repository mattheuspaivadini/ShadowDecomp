/* STATUS: NON_MATCHING (Session 4, 2026-10-14) - but see docs/compiler.md 4.2.
 * The MULTIPLY SHAPE now matches: the original materialises the stride in a
 * register and uses the R5900 3-operand `mult rd,rs,rt`, which ee-gcc2.96 only
 * emits for a *runtime* multiplier (a literal is expanded into a shift/add
 * sequence; see tools/cc/probe_mult*.sh). Writing the stride as a local
 * variable reproduces `addiu v1,$zero,0x184; mult a0,a0,v1`.
 * What still differs is register allocation: the original keeps the base in
 * $v0 and the product in $a0 and adds into the delay slot; ours keeps the base
 * in $at and the product in $v0. Allocation family (docs/compiler.md section 4).
 */
/* asm/cod/020F18.s -> func_00120F18 @ 0x00120F18 (0x18 bytes)
 *   addiu $v1, $zero, 0x184
 *   lui   $v0, %hi(D_00135638)
 *   mult  $a0, $a0, $v1              ; i * 0x184  (R5900 3-operand MULT)
 *   addiu $v0, $v0, %lo(D_00135638)
 *   jr    $ra
 *    addu $v0, $a0, $v0              ; &D_00135638[i]
 *
 * The stride is materialised in a register and multiplied with the R5900
 * 3-operand MULT, i.e. it was a *runtime* value at RTL-expansion time (a literal
 * would have been expanded into a shift/add sequence by this compiler; see
 * tools/cc/probe_mult*.sh). Reproduced here with a local `size` variable.
 * The 0x184 element stride is evidence-backed; the element content UNCONFIRMED.
 */
struct S020F18 {
    char bytes[0x184];
};

extern struct S020F18 D_00135638[];

struct S020F18 *func_00120F18(int i) {
    int size = 0x184;

    return (struct S020F18 *)((char *)D_00135638 + i * size);
}
