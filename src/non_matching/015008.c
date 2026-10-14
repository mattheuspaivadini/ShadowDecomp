/* STATUS: NON_MATCHING (Session 4, 2026-10-14).
 * 15 instructions differ. The original materialises the stored `1` before the
 * two `lui`s, addresses D_001339E8 absolutely with `sw $v1,%lo(D)($v0)`, and
 * uses a plain `slt` + `bnez` pointer loop with a `nop` delay slot. Ours emits
 * the `lui`s first, uses `sltu` and rotates the loop into `bnezl` with the body
 * load in the delay slot. Tried: indexed for-loop, pointer for-loop, do-while.
 */
/* asm/cod/015008.s -> func_00115008 @ 0x00115008 (0x40 bytes)
 *   addiu $v1, $zero, 0x1
 *   lui   $v0, %hi(D_001339E8)
 *   lui   $a0, %hi(D_0014B598)
 *   sw    $v1, %lo(D_001339E8)($v0)      ; D_001339E8 = 1
 *   addiu $a0, $a0, %lo(D_0014B598)      ; p = D_0014B598
 *   addiu $v1, $a0, 0x3340               ; end = p + 16 * 0x334
 * .Lloop:
 *   sw    $zero, 0x0($a0)
 *   sw    $zero, 0x4($a0)
 *   sw    $zero, 0x8($a0)
 *   sw    $zero, 0xC($a0)
 *   addiu $a0, $a0, 0x334                ; next record
 *   slt   $v0, $a0, $v1
 *   bnez  $v0, .Lloop
 *    nop
 *   jr    $ra
 *    addiu $v0, $zero, 0x1               ; return 1
 *
 * D_001339E8 lives in .data and is addressed absolutely by the original, so it
 * is declared non-small (see include/symbols.h). The 0x334 record stride and the
 * 16-record extent are evidence-backed; the record content is UNCONFIRMED.
 */
extern __attribute__((section(".data"))) int D_001339E8;

struct S015008 {
    int field0;         /* 0x0 */
    int field4;         /* 0x4 */
    int field8;         /* 0x8 */
    int fieldC;         /* 0xC */
    char rest[0x324];   /* to 0x334 */
};

extern struct S015008 D_0014B598[];

int func_00115008(void) {
    struct S015008 *p = D_0014B598;
    struct S015008 *end = (struct S015008 *)((char *)D_0014B598 + 0x3340);

    D_001339E8 = 1;
    do {
        p->field0 = 0;
        p->field4 = 0;
        p->field8 = 0;
        p->fieldC = 0;
        p = (struct S015008 *)((char *)p + 0x334);
    } while (p < end);
    return 1;
}
