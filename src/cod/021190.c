/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/021190/batch2.json (v02_double_index, cc=29, score 0).
 *
 * asm/cod/021190.s -> func_00121190 @ 0x00121190 (0x28 bytes)
 *   addiu $v0, $zero, 0x24
 *   lui   $v1, %hi(D_00163CC8)
 *   mult  $a0, $a0, $v0                ; i * 0x24  (R5900 mult, 2.9 shape)
 *   addiu $v1, $v1, %lo(D_00163CC8)
 *   addiu $v0, $zero, 0x1
 *   addu  $a3, $v1, $a0                ; p = &D_00163CC8[i]
 *   daddu $v1, $a3, $zero              ; redundant copy: second indexing
 *   sw    $a1, 0x1C($a3)               ; p->field1C = a
 *   jr    $ra
 *    sw   $a2, 0x20($v1)               ; p->field20 = b
 *
 * Matching note: the original indexes the struct array *twice*
 * (`D_00163CC8[i].field1C = a; D_00163CC8[i].field20 = b;`). GCC's CSE reuses
 * the `mult` but materialises the second element address as a plain copy of
 * the first (`daddu $v1,$a3,$zero`) — the shape a single `p` local cannot
 * produce. The struct's `sizeof` is what turns the index into the `mult`
 * (`0x24`); cc=29 only.
 */
struct S021190 {
    char pad00[0x1C];
    int  field1C;   /* 0x1C */
    int  field20;   /* 0x20 */
};

extern struct S021190 D_00163CC8[];

int func_00121190(int i, int a, int b) {
    D_00163CC8[i].field1C = a;
    D_00163CC8[i].field20 = b;
    return 1;
}
