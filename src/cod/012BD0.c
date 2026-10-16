/* Phase 3 flag-pinning case (globals + addressing mode).
 * asm/cod/012BD0.s -> func_00112BD0 @ 0x00112BD0 (0x14 bytes)
 *   lui   $v1, %hi(D_0014B358)
 *   addiu $v1, $v1, %lo(D_0014B358)
 *   lw    $v0, 0x14($v1)
 *   sw    $a1, 0x18($v1)
 *   jr    $ra
 *    sw   $a0, 0x14($v1)
 */
struct S0014B358 {
    char pad00[0x14];
    int  field14;   /* 0x14 */
    int  field18;   /* 0x18 */
};

extern struct S0014B358 D_0014B358;

int sceSifSetCmdBuffer(int a, int b) {
    int v = D_0014B358.field14;
    D_0014B358.field18 = b;
    D_0014B358.field14 = a;
    return v;
}
