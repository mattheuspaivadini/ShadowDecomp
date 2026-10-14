/* Phase 3 flag-pinning case.
 * asm/cod/0128C0.s -> func_001128C0 @ 0x001128C0 (0x10 bytes, last word is padding)
 *   lw   $v0, 0x10($a0)
 *   jr   $ra
 *    sw  $v0, 0x08($a1)
 *   nop            <- alignment padding to the next function
 */
int func_001128C0(int *a, int *b) {
    int v = a[4];
    b[2] = v;
    return v;
}
