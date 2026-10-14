/* Phase 3 flag-pinning case (no relocations: pure register-relative stores).
 * asm/cod/012908.s -> func_00112908 @ 0x00112908 (0x10 bytes, last word padding)
 *   lui   $v0, %hi(D_0014B358)      <- has a relocation (masked in the compare)
 *   jr    $ra
 *    addiu $v0, $v0, %lo(D_0014B358)
 */
extern char D_0014B358[];

char *func_00112908(void) {
    return D_0014B358;
}
