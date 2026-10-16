/* asm/cod/0028F0.s -> func_001028F0 @ 0x001028F0 (0x30 bytes)
 *   lui   $v0, %hi(D_0013B790)
 *   daddu $a1, $zero, $zero        ; i = 0
 *   addiu $v1, $v0, %lo(D_0013B790) ; p = D_0013B790
 *   addiu $a2, $zero, -1
 * .Lloop:
 *   lw    $v0, 0x0($v1)
 *   bnel  $v0, $a0, .Lnext
 *    addiu $a1, $a1, 0x1
 *   sw    $a2, 0x0($v1)            ; *p = -1
 *   jr    $ra
 *    daddu $v0, $a0, $zero         ; return key
 * .Lnext:
 *   slti  $v0, $a1, 0x100
 *   bnez  $v0, .Lloop
 *    addiu $v1, $v1, 0x4
 *   jr    $ra
 *    addiu $v0, $zero, -1          ; return -1
 *
 * D_0013B790 is a 256-entry int table in .bss (size 0x400, evidence:
 * asm/data/cod/0013A200.bss.s), so it is *not* small data -> absolute address.
 */
extern int D_0013B790[256];

int LoaderSysDeleteExternalThreadList(int key) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] == key) {
            D_0013B790[i] = -1;
            return key;
        }
    }
    return -1;
}
