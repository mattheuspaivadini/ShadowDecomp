/* asm/cod/012088.s -> func_00112088 @ 0x00112088 (0x18 bytes)
 *   addiu $v0, $zero, 0x2000
 *   sd    $zero, 0x48($a1)
 *   sw    $v0, 0x4($a1)
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * $a0 is unused; $a1 points to a structure with a 32-bit field at 0x4 (set to
 * 0x2000) and a 64-bit field at 0x48 (cleared).
 */
struct S00112088 {
    char      pad00[0x04];
    int       field04;   /* 0x04 */
    char      pad08[0x40];
    long long field48;   /* 0x48 */
};

int fstat(int unused, struct S00112088 *p) {
    p->field48 = 0;
    p->field04 = 0x2000;
    return 0;
}
