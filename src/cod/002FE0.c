/* Phase 3 flag-pinning case.
 * asm/cod/002FE0.s -> func_00102FE0 @ 0x00102FE0 (8 bytes)
 *   jr   $ra
 *    addiu $v0, $zero, 2
 */
int LoaderSysCheckCDBootMode(void) {
    return 2;
}
