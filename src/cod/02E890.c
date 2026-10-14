/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/02E890/batch1.json (v06_index_twice, score 0 with BOTH
 * ee-gcc2.96 and 2.9-991111-01).
 *
 * asm/cod/02E890.s -> func_0012E890 @ 0x0012E890 (0x2C bytes, last word pad)
 *   beqz  $a1, .L0012E8B4
 *    nop
 *   lw    $v0, 0x4($a1)
 *   lw    $a0, 0x4C($a0)
 *   sll   $v0, $v0, 2
 *   addu  $v0, $v0, $a0
 *   lw    $v1, 0x0($v0)
 *   sw    $v1, 0x0($a1)
 *   sw    $a1, 0x0($v0)
 * .L0012E8B4:
 *   jr    $ra
 *    nop
 *
 * A singly-linked-list unlink from a bucket table: `a` holds a pointer table
 * at 0x4C, `b` holds a link field at 0x0 and a bucket index at 0x4.
 *
 * Matching note: the winning shape indexes the table *twice* instead of
 * caching a `slot` local:
 *     b->field00 = a->field4C[b->field04];
 *     a->field4C[b->field04] = (int)b;
 * CSE still folds the address computation, but the allocator now keeps the
 * table pointer in `$a0` (the dead argument register) exactly like the
 * original, where a `slot` local scores 5 (register roles swapped).
 */
struct S02E890_A {
    char pad00[0x4C];
    int *field4C;   /* 0x4C: bucket table */
};
struct S02E890_B {
    int field00;   /* 0x00: next link */
    int field04;   /* 0x04: bucket index */
};

void func_0012E890(struct S02E890_A *a, struct S02E890_B *b) {
    if (b != 0) {
        b->field00 = a->field4C[b->field04];
        a->field4C[b->field04] = (int)b;
    }
}
