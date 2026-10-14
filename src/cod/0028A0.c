/* asm/cod/0028A0.s -> func_001028A0 @ 0x001028A0 (0x4C bytes)
 *   lui   $v0, %hi(D_0013BF90)
 *   daddu $a1, $zero, $zero            ; i = 0
 *   addiu $v0, $v0, %lo(D_0013BF90)    ; base
 *   addiu $a2, $zero, -0x1
 *   addiu $v1, $v0, 0x4                ; &pair[0].field04
 * .L001028B8:
 *   lw    $v0, 0x0($v1)
 *   bnel  $v0, $a0, .L001028D8
 *    addiu $a1, $a1, 0x1               ; i++
 *   sw    $a2, -0x4($v1)               ; pair.field00 = -1
 *   daddu $v0, $a0, $zero              ; return key
 *   jr    $ra
 *    sw   $a2, 0x0($v1)                ; pair.field04 = -1
 * .L001028D8:
 *   slti  $v0, $a1, 0x100
 *   bnez  $v0, .L001028B8
 *    addiu $v1, $v1, 0x8               ; &pair[i+1].field04
 *   jr    $ra
 *    addiu $v0, $zero, -0x1
 *
 * Find the pair whose field04 matches `key`, clear both words to -1, return key;
 * -1 if not found. D_0013BF90 is an array of 8-byte pairs.
 */
struct P0028A0 {
    int field00;   /* 0x00 */
    int field04;   /* 0x04 */
};

extern struct P0028A0 D_0013BF90[];

int func_001028A0(int key) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].field04 == key) {
            D_0013BF90[i].field04 = -1;
            D_0013BF90[i].field00 = -1;
            return key;
        }
    }
    return -1;
}
