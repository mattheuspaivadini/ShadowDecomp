/* STATUS (Session 4, 2026-10-14): NON_MATCHING. record key search; only the order of `+0xD0` vs the base add differs (3 instructions).
 * The original .s stays in the build (asm/cod/020D10.s); this C
 * attempt is kept for the record. */
/* asm/cod/020D10.s -> func_00120D10 @ 0x00120D10 (0x48 bytes)
 *   addiu $v1, $zero, 0x184
 *   lui   $v0, %hi(D_00135638)
 *   mult  $a0, $a0, $v1                ; index * 0x184
 *   addiu $v0, $v0, %lo(D_00135638)
 *   daddu $v1, $zero, $zero
 *   addu  $a0, $a0, $v0
 *   addiu $a0, $a0, 0xD0               ; + 0xD0 (32-int key array)
 * .L00120D30:
 *   lw    $v0, 0x0($a0)
 *   bne   $v0, $a1, .L00120D44
 *    addiu $v1, $v1, 0x1
 *   jr    $ra
 *    addiu $v0, $zero, 0x1
 * .L00120D44:
 *   slti  $v0, $v1, 0x20
 *   bnez  $v0, .L00120D30
 *    addiu $a0, $a0, 0x4
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * Search the 32-entry key array at +0xD0 of record `index` (stride 0x184) in
 * D_00135638. Uses the R5900 3-operand constant `mult` (2.9 generation).
 */
struct R020D10 {
    char pad00[0xD0];
    int  keys[32];   /* 0xD0 */
    char pad150[0x34];
};

extern struct R020D10 D_00135638[];

int func_00120D10(int index, int key) {
    int i;

    for (i = 0; i < 32; i++) {
        if (D_00135638[index].keys[i] == key)
            return 1;
    }
    return 0;
}
