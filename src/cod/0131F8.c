/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/0131F8/batch3.json (v07_adjust_first, score 0 with BOTH
 * ee-gcc2.96 and 2.9-991111-01).
 *
 * asm/cod/0131F8.s -> func_001131F8 @ 0x001131F8 (0x2C bytes)
 *   lw    $v0, 0x0($a0)      ; a = p->field00
 *   lw    $a1, 0xC($a0)      ; b = p->field0C
 *   addiu $v0, $v0, -0x4     ; a - 1 (element)
 *   sw    $zero, 0xC($a0)    ; p->field0C = 0
 *   subu  $v0, $v0, $a1      ; (a - 1) - b
 *   lw    $v1, 0x0($a1)      ; old = *b
 *   sra   $v0, $v0, 2        ; pointer difference -> elements
 *   srl   $v0, $v0, 2        ; unsigned count shift
 *   addu  $v1, $v1, $v0
 *   jr    $ra
 *    sw   $v1, 0x0($a1)      ; *b = old + count
 *
 * Matching note: the subtract must be staged as `a = a - 1;` *before* the
 * pointer difference, otherwise ee-gcc reassociates and transposes the
 * `addiu`/`subu` pair (score 5). The `sra`+`srl` pair is the pointer-difference
 * division followed by an unsigned `>> 2` on the count. Struct field layout
 * (0x00/0x0C) is evidence-backed; meaning UNCONFIRMED.
 */
struct S001131F8 {
    int *field00;   /* 0x00 */
    char pad04[0x08];
    int *field0C;   /* 0x0C */
};

void sceVif1PkCloseDirectCode(struct S001131F8 *p) {
    int *a = p->field00;
    int *b = p->field0C;
    unsigned n;

    a = a - 1;
    p->field0C = 0;
    n = (unsigned)(a - b);
    *b += n >> 2;
}
