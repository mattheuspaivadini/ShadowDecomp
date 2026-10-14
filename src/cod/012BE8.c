/* asm/cod/012BE8.s -> func_00112BE8 @ 0x00112BE8 (0x14 bytes)
 *   lui   $v1, %hi(D_0014B358)
 *   addiu $v1, $v1, %lo(D_0014B358)
 *   lw    $v0, 0xC($v1)
 *   sw    $a1, 0x10($v1)
 *   jr    $ra
 *    sw   $a0, 0xC($v1)
 */
struct S0014B358 {
    char pad00[0x0C];
    int  field0C;   /* 0x0C */
    int  field10;   /* 0x10 */
};

extern struct S0014B358 D_0014B358;

int func_00112BE8(int a, int b) {
    int v = D_0014B358.field0C;
    D_0014B358.field10 = b;
    D_0014B358.field0C = a;
    return v;
}
