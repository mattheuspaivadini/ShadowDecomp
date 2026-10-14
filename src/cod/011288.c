/* asm/cod/011288.s -> func_00111288 @ 0x00111288 (0x48 bytes)
 *   srl   $v0, $a0, 10
 *   bltz  $a0, .L001112A4
 *    sll  $a1, $v0, 6              ; base = (index >> 10) << 6
 *   lw    $v1, 0x8($a1)
 *   andi  $v0, $a0, 0x3FF
 *   beql  $v0, $v1, .L001112AC
 *    lw   $v0, 0xC($a1)
 * .L001112A4:
 *   jr    $ra
 *    addiu $v0, $zero, -0x1
 * .L001112AC:
 *   andi  $v0, $v0, 0x1
 *   beqz  $v0, .L001112C8
 *    nop
 *   ld    $v1, 0x18($a1)
 *   ld    $v0, 0x10($a1)
 *   jr    $ra
 *    dsubu $v0, $v0, $v1
 * .L001112C8:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * Guarded record access: the record base is derived from the high bits of
 * `index` (>> 10, * 64); the low 10 bits are a tag that must match field08.
 * Returns a 64-bit delta (field10 - field18) or 0/-1.
 * The `>> 10` is logical (srl) although the `bltz` guard is signed, so the
 * index is read as unsigned with a signed sign-check.
 */
struct S011288 {
    char      pad00[0x08];
    int       field08;   /* 0x08 tag */
    int       field0C;   /* 0x0C flags */
    long long field10;   /* 0x10 */
    long long field18;   /* 0x18 */
};

long long func_00111288(unsigned int index) {
    struct S011288 *p;

    if ((int)index < 0)
        return -1;
    p = (struct S011288 *)((index >> 10) << 6);
    if ((index & 0x3FF) != (unsigned int)p->field08)
        return -1;
    if (p->field0C & 1)
        return p->field10 - p->field18;
    return 0;
}
