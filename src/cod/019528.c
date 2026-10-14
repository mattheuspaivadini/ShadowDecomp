/* asm/cod/019528.s -> func_00119528 @ 0x00119528 (0x20 bytes)
 *   jal func_00119498
 *    addiu a4,zero,0x21
 * Forwards a0-a3 and passes 0x21 as the fifth argument.
 */
extern int func_00119498();

int func_00119528(int a0, int a1, int a2, int a3) {
    return func_00119498(a0, a1, a2, a3, 0x21);
}
