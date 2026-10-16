/* asm/cod/00E9D0.s -> func_0010E9D0 @ 0x0010E9D0 (0x20 bytes)
 *   addiu sp,sp,-0x20
 *   sd ra,0x10(sp)
 *   jal func_0010E400
 *    daddu a3,sp,zero          ; fourth argument points at a 16-byte local
 *   ld ra,0x10(sp); jr ra; addiu sp,sp,0x20
 * Forwards a0-a2 and passes a stack buffer as the fourth argument.
 */
extern int func_0010E400();

int sceSifLoadModuleBuffer(int a0, int a1, int a2) {
    int local[4];

    return func_0010E400(a0, a1, a2, local);
}
