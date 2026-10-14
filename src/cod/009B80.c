/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/009B80/batch2.json (v03_goto, cc=29, score 0).
 *
 * asm/cod/009B80.s -> func_00109B80 @ 0x00109B80 (0x3C bytes)
 *   lw    $a1, 0x0($a0)      ; p = a[0]
 *   beqz  $a1, .L00109BAC
 *    nop
 *   lw    $v1, 0x4($a0)      ; a[1]
 *   lw    $v0, 0x18($a1)     ; p->field18
 *   bne   $v1, $v0, .L00109BAC
 *    nop
 *   lw    $v0, 0x10($a1)     ; p->field10
 *   andi  $v0, $v0, 0x1
 *   bnez  $v0, .L00109BB4
 *    nop
 * .L00109BAC:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 * .L00109BB4:
 *   jr    $ra
 *    addiu $v0, $zero, 0x1
 *
 * Matching note: the original keeps *three* return blocks; every `return`
 * spelling without explicit label targets is merged by ee-gcc into one shared
 * epilogue with the constants in the branch delay slots (best score 7). The
 * goto shape below reproduces the original's separate `jr` blocks exactly
 * (cc=29). Field offsets 0x10/0x18 are evidence-backed only.
 */
struct S009B80 {
    char pad00[0x10];
    int  field10;   /* 0x10 */
    char pad14[4];
    int  field18;   /* 0x18 */
};

int func_00109B80(int *a) {
    struct S009B80 *p = (struct S009B80 *)a[0];

    if (p == 0)
        goto ret0;
    if (a[1] != p->field18)
        goto ret0;
    if (p->field10 & 1)
        goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}
