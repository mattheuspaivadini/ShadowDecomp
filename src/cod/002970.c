/* asm/cod/002970.s -> func_00102970 @ 0x00102970 (0x54 bytes)
 *   lui   $v1, %hi(D_0013C790)
 *   daddu $a2, $zero, $zero
 *   addiu $a4, $v1, %lo(D_0013C790)
 *   lw    $v0, 0x0($a4)
 * .L00102980:
 *   addiu $a4, $a4, 0x4
 *   daddu $a3, $a2, $zero
 *   addiu $a2, $a2, 0x1
 *   beq   $v0, $a0, .L001029A8
 *    slti $a1, $a2, 0x100
 *   bnel  $a1, $zero, .L00102980
 *    lw   $v0, 0x0($a4)
 *   addiu $a3, $zero, -0x1
 * .L001029A8:
 *   bltz  $a3, .L001029BC
 *    addiu $v1, $v1, %lo(D_0013C790)
 *   sll   $v0, $a3, 2
 *   addu  $v0, $v0, $v1
 *   sw    $zero, 0x0($v0)             ; D[idx] = 0
 * .L001029BC:
 *   jr    $ra
 *    daddu $v0, $a3, $zero            ; return idx
 *
 * Find `key` in the 256-int table D_0013C790; on a hit clear the entry and
 * return the index, otherwise -1. Same shape as func_001028F0 (early return).
 */
extern int D_0013C790[256];

int func_00102970(int key) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] == key) {
            D_0013C790[i] = 0;
            return i;
        }
    }
    return -1;
}
