/* asm/cod/0131F8.s -> func_001131F8 @ 0x001131F8 (0x30 bytes)
 *   lw    $v0, 0x0($a0)
 *   lw    $a1, 0xC($a0)
 *   addiu $v0, $v0, -0x4
 *   sw    $zero, 0xC($a0)
 *   subu  $v0, $v0, $a1
 *   lw    $v1, 0x0($a1)
 *   sra   $v0, $v0, 2
 *   srl   $v0, $v0, 2
 *   addu  $v1, $v1, $v0
 *   jr    $ra
 *    sw   $v1, 0x0($a1)
 *
 * STATUS (2026-10-14): NON_MATCHING - the instruction set is understood but the
 * `sra`/`srl` pair (an unsigned shift of a pointer difference) and the reload
 * ordering were not reproduced by the C spellings tried.
 */
struct S001131F8 {
    int *field00;   /* 0x00 */
    char pad04[0x08];
    int *field0C;   /* 0x0C */
};

void func_001131F8(struct S001131F8 *p) {
    int *a = p->field00;
    int *b = p->field0C;

    p->field0C = 0;
    *b += ((unsigned)(((char *)a - 4) - (char *)b)) >> 2;
}
