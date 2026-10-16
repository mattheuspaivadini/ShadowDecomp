/* MATCHING (Session 4, 2026-10-14) with the ALTERNATE EE-GCC revision
 * (manifest token `cc=29` = ee-gcc2.9-991111-01); both the `mult` constant
 * stride and the separate fall-through body block match. See 4.2/4.3.
 *
 * asm/cod/022018.s -> func_00122018 @ 0x00122018 (0x30 bytes)
 *   sltiu $v0, $a0, 0x2
 *   bnez  $v0, .Lbody
 *    addiu $v1, $zero, 0x24
 *   jr    $ra
 *    daddu $v0, $zero, $zero            ; return 0
 * .Lbody:
 *   lui   $v0, %hi(D_00163CC8)
 *   mult  $v1, $a0, $v1                 ; i * 0x24
 *   addiu $v0, $v0, %lo(D_00163CC8)
 *   addu  $v1, $v1, $v0
 *   lw    $v0, 0x0($v1)                 ; D_00163CC8[i].field0
 *   jr    $ra
 *    sltu $v0, $zero, $v0               ; return field0 != 0
 */
struct S022018 {
    int  field0;    /* 0x0 */
    char pad04[0x20];
};

extern struct S022018 D_00163CC8[];

int _sceMcCoreCheckSocket(unsigned int i) {
    if (i >= 2)
        return 0;
    return ((struct S022018 *)((char *)D_00163CC8 + i * 0x24))->field0 != 0;
}
