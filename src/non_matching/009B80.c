/* STATUS: NON_MATCHING (Session 4, 2026-10-14).
 * Compiled 56 B vs the original 60 B. The original keeps three distinct return
 * blocks - `jr $ra; daddu $v0,zero,zero` (shared by both early exits, with a
 * `nop` delay slot) and `jr $ra; addiu $v0,zero,1` - reached by `bnez`. With
 * every spelling tried (early returns / nested if / explicit `== 0`),
 * ee-gcc2.96 instead materialises the boolean with `sltu`, hoists the return
 * value into the branch delay slots and uses a single `jr`. Same family as the
 * block-layout entries in docs/compiler.md section 4.
 */
/* asm/cod/009B80.s -> func_00109B80 @ 0x00109B80 (0x20 bytes)
 *   lw    $a1, 0x0($a0)      ; p = a[0]
 *   beqz  $a1, .Lret0
 *   lw    $v1, 0x4($a0)      ; a[1]
 *   lw    $v0, 0x18($a1)     ; p->field18
 *   bne   $v1, $v0, .Lret0
 *   lw    $v0, 0x10($a1)     ; p->field10
 *   andi  $v0, $v0, 0x1
 *   bnez  $v0, .Lret1
 * .Lret0:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 * .Lret1:
 *   jr    $ra
 *    addiu $v0, $zero, 0x1
 *
 * Field layout is evidence-backed by the offsets 0x10 / 0x18 only; the object
 * type itself is UNCONFIRMED.
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
        return 0;
    if (a[1] == p->field18) {
        if (p->field10 & 1)
            return 1;
    }
    return 0;
}
