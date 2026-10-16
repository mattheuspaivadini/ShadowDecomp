/* asm/cod/00EC38.s -> func_0010EC38 @ 0x0010EC38 (0x24 bytes)
 *   addiu sp,sp,-0x20
 *   daddu a4,zero,zero
 *   sd ra,0x10(sp)
 *   jal func_0010EA10
 *    daddu a3,sp,zero          ; fourth argument points at a 16-byte local
 *   ld ra,0x10(sp); jr ra; addiu sp,sp,0x20
 * Forwards a0-a2, passes a stack buffer fourth and 0 fifth.
 */
extern int func_0010EA10();

int sceSifLoadModule(int a0, int a1, int a2) {
    int local[4];

    return func_0010EA10(a0, a1, a2, local, 0);
}
