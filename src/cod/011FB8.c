/* Phase 3 flag-pinning case.
 * asm/cod/011FB8.s -> func_00111FB8 @ 0x00111FB8 (8 bytes)
 *   jr   $ra
 *    addiu $v0, $zero, -1
 */
int func_00111FB8(void) {
    return -1;
}
