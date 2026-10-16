/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/0220F8/batch2.json (v03_reversed, cc=29, score 0).
 *
 * asm/cod/0220F8.s -> func_001220F8 @ 0x001220F8 (0x30 bytes)
 *   addiu $v0, $zero, 0x24
 *   lui   $v1, %hi(D_00163CC8)
 *   mult  $a0, $a0, $v0                 ; i * 0x24  (runtime stride)
 *   addiu $a1, $v1, %lo(D_00163CC8)
 *   addu  $v0, $a0, $a1
 *   lw    $v1, 0x0($v0)                 ; field0
 *   bnez  $v1, .L00122120
 *    addu $v1, $a1, $a0                  ; &D_00163CC8[i] (recomputed)
 *   jr    $ra
 *    addiu $v0, $zero, -0x1              ; return -1
 * .L00122120:
 *   jr    $ra
 *    lw   $v0, 0x4($v1)                  ; return field4
 *
 * Matching note: `if (D_00163CC8[i].field0 == 0) return -1;` — the *reversed*
 * test plus double indexing makes ee-gcc rematerialise the element address in
 * the taken branch's delay slot (`addu $v1,$a1,$a0`) exactly like the
 * original; the un-reversed spelling (`!= 0` first) leaves the delay slot
 * empty (score 5-10). cc=29 only.
 */
struct S0220F8 {
    int  field0;    /* 0x0 */
    int  field4;    /* 0x4 */
    char pad08[0x1C];
};

extern struct S0220F8 D_00163CC8[];

int _sceMcCoreChangeSocketTypeMc2Dbc(int i) {
    if (D_00163CC8[i].field0 == 0)
        return -1;
    return D_00163CC8[i].field4;
}
