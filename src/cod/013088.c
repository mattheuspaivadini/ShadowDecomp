/* Phase 3 flag-pinning case.
 * asm/cod/013088.s -> func_00113088 @ 0x00113088 (0x10 bytes)
 *   lw   $v0, 0x4($a0)
 *   sw   $zero, 0x8($a0)
 *   jr   $ra
 *    sw  $v0, 0x0($a0)
 */
int sceVif1PkReset(int *p) {
    int v = p[1];
    p[2] = 0;
    p[0] = v;
    return v;
}
