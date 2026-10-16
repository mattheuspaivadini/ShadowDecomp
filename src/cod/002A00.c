/* asm/cod/002A00.s -> func_00102A00 @ 0x00102A00 (0x3C bytes)
 *   lui   $v0, %hi(D_0013BB90)
 *   addiu $a0, $zero, -1
 *   addiu $v0, $v0, %lo(D_0013BB90)   ; p = D_0013BB90
 *   addiu $v1, $zero, 0xFF             ; i = 255
 *   addiu $v0, $v0, 0x3FC              ; p = &D[255]
 * .Lloop:
 *   addiu $v1, $v1, -0x1
 *   sw    $a0, 0x0($v0)                ; *p = -1
 *   bgez  $v1, .Lloop
 *    addiu $v0, $v0, -0x4              ; p--
 *   jr    $ra
 *    nop
 *
 * D_0013BB90 is the 256-entry int table in .bss (size 0x400).
 * The `-1` is materialised first, before the loop bound, so it is written as a
 * local initialised before the loop (evidence: instruction order).
 */
extern int D_0013BB90[256];

void LoaderSysInitExternalSemaList(void) {
    int value = -1;
    int i;

    for (i = 255; i >= 0; i--)
        D_0013BB90[i] = value;
}
