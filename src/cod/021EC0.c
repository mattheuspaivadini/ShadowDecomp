/* asm/cod/021EC0.s -> func_00121EC0 @ 0x00121EC0 (0x38 bytes)
 *   lui   $v0, %hi(D_00163CC8)
 *   daddu $v1, $zero, $zero          ; i = 0
 *   addiu $a0, $v0, %lo(D_00163CC8)  ; p = D_00163CC8
 * .L00121ED0:
 *   lw    $v0, 0x0($a0)              ; p->field00
 *   bnel  $v0, $zero, .L00121EE4
 *    addiu $v1, $v1, 0x1             ; i++
 *   jr    $ra
 *    daddu $v0, $v1, $zero           ; return i
 * .L00121EE4:
 *   slti  $v0, $v1, 0x2
 *   bnez  $v0, .L00121ED0
 *    addiu $a0, $a0, 0x24            ; p += 0x24
 *   jr    $ra
 *    addiu $v0, $zero, -0x1          ; return -1
 *
 * Find the first free slot (field00 == 0) among the first two records of
 * D_00163CC8 (stride 0x24).
 */
struct R021EC0 {
    int  field00;   /* 0x00 zero == free */
    char pad04[0x20];
};

extern struct R021EC0 D_00163CC8[];

int func_00121EC0(void) {
    int i;

    for (i = 0; i < 2; i++) {
        if (D_00163CC8[i].field00 == 0)
            return i;
    }
    return -1;
}
