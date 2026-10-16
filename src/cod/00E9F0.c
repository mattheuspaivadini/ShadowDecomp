/* asm/cod/00E9F0.s -> func_0010E9F0 @ 0x0010E9F0 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_0010E400
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * Forwards a0-a3 unchanged and returns the callee's value.
 */
extern int func_0010E400();

int sceSifLoadStartModuleBuffer(int a0, int a1, int a2, int a3) {
    return func_0010E400(a0, a1, a2, a3);
}
