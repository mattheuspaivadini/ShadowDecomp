/* STATUS: NON_MATCHING (Session 4, 2026-10-14) - one instruction short.
 * The `mult` now matches (runtime stride, see 020F18.c and docs/compiler.md
 * 4.2) but the original also contains a redundant `daddu $v1,$a3,$zero` copy
 * before the two stores that ee-gcc2.96 does not emit (36 B vs 40 B).
 */
/* asm/cod/021190.s -> func_00121190 @ 0x00121190 (0x28 bytes)
 *   addiu $v0, $zero, 0x24
 *   lui   $v1, %hi(D_00163CC8)
 *   mult  $a0, $a0, $v0                ; i * 0x24  (runtime stride)
 *   addiu $v1, $v1, %lo(D_00163CC8)
 *   addiu $v0, $zero, 0x1
 *   addu  $a3, $v1, $a0                ; p = &D_00163CC8[i]
 *   daddu $v1, $a3, $zero
 *   sw    $a1, 0x1C($a3)               ; p->field1C = a
 *   jr    $ra
 *    sw   $a2, 0x20($v1)               ; p->field20 = b
 */
struct S021190 {
    char pad00[0x1C];
    int  field1C;   /* 0x1C */
    int  field20;   /* 0x20 */
};

extern struct S021190 D_00163CC8[];

int func_00121190(int i, int a, int b) {
    int size = 0x24;
    struct S021190 *p = (struct S021190 *)((char *)D_00163CC8 + i * size);

    p->field1C = a;
    p->field20 = b;
    return 1;
}
