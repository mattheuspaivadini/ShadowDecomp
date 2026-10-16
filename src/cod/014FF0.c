/* asm/cod/014FF0.s -> func_00114FF0 @ 0x00114FF0 (0x14 bytes)
 *   lw    $v0, 0x0($a0)
 *   sw    $a1, 0x0($a0)
 *   srl   $v0, $v0, 8
 *   jr    $ra
 *    andi $v0, $v0, 1
 */
int sceDmaRestart(unsigned int *p, unsigned int value) {
    unsigned int old = *p;
    *p = value;
    return (old >> 8) & 1;
}
