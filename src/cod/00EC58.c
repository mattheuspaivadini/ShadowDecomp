/* asm/cod/00EC58.s -> func_0010EC58 @ 0x0010EC58 (0x20 bytes)
 *   jal func_0010EA10
 *    daddu a4,zero,zero
 * Forwards a0-a3 and zeroes the fifth argument.
 */
extern int func_0010EA10();

int func_0010EC58(int a0, int a1, int a2, int a3) {
    return func_0010EA10(a0, a1, a2, a3, 0);
}
