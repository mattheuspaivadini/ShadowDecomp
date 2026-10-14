/* asm/cod/019AA0.s -> func_00119AA0 @ 0x00119AA0 (0x1C bytes)
 *   lw    $v1, 0x10($a0)
 *   lui   $v0, (0xFFFFFFFE >> 16)
 *   ori   $v0, $v0, (0xFFFFFFFE & 0xFFFF)
 *   sw    $zero, 0x18($a0)
 *   and   $v1, $v1, $v0
 *   jr    $ra
 *    sw   $v1, 0x10($a0)
 *
 * Bit clear on a field + sibling zero store; same shape as func_00109268.
 */
struct S00119AA0 {
    char pad00[0x10];
    int  field10;   /* 0x10 */
    int  field14;   /* 0x14 */
    int  field18;   /* 0x18 */
};

void func_00119AA0(struct S00119AA0 *p) {
    p->field10 &= 0xFFFFFFFE;
    p->field18 = 0;
}
