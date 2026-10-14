/* asm/cod/0220B0.s -> func_001220B0 @ 0x001220B0 (0x44 bytes)
 *   lui   $v0, %hi(D_00163CC8)
 *   daddu $v1, $zero, $zero          ; i = 0
 *   addiu $a1, $v0, %lo(D_00163CC8)  ; p = D_00163CC8
 * .L001220C0:
 *   lw    $v0, 0x0($a1)              ; p->field00
 *   beql  $v0, $zero, .L001220E0
 *    addiu $v1, $v1, 0x1             ; i++
 *   lw    $v0, 0x4($a1)              ; p->field04
 *   bnel  $v0, $a0, .L001220E0
 *    addiu $v1, $v1, 0x1             ; i++
 *   jr    $ra
 *    daddu $v0, $v1, $zero           ; return i
 * .L001220E0:
 *   slti  $v0, $v1, 0x2
 *   bnez  $v0, .L001220C0
 *    addiu $a1, $a1, 0x24            ; p += 0x24
 *   jr    $ra
 *    addiu $v0, $zero, -0x1          ; return -1
 *
 * Find the (in-use) record whose field04 matches `key` among the first two
 * records of D_00163CC8 (stride 0x24). Evidence for the layout: the sibling
 * accessors func_00121EC0/_001220F8/dump in docs/structs.md.
 */
struct R0220B0 {
    int  field00;   /* 0x00 non-zero == in use */
    int  field04;   /* 0x04 key */
    char pad08[0x1C];
};

extern struct R0220B0 D_00163CC8[];

int func_001220B0(int key) {
    int i;

    for (i = 0; i < 2; i++) {
        if (D_00163CC8[i].field00 != 0 && D_00163CC8[i].field04 == key)
            return i;
    }
    return -1;
}
