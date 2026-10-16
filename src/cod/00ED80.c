/* asm/cod/00ED80.s -> func_0010ED80 @ 0x0010ED80 (0x20 bytes)
 *   jal func_0010EC78
 *    addiu a3,zero,0x1
 * Forwards a0-a2 and passes 1 as the fourth argument.
 */
extern int func_0010EC78();

int sceSifLoadElfPart(int a0, int a1, int a2) {
    return func_0010EC78(a0, a1, a2, 1);
}
