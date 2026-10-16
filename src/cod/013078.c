/* asm/cod/013078.s -> func_00113078 @ 0x00113078 (0x10 bytes)
 *   sw   $a1, 0x0($a0)
 *   sw   $zero, 0x8($a0)
 *   jr   $ra
 *    sw  $a1, 0x4($a0)
 */
void sceVif1PkInit(int *p, int value) {
    p[1] = value;
    p[0] = value;
    p[2] = 0;
}
