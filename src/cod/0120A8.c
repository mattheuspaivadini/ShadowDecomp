/* asm/cod/0120A8.s -> func_001120A8 @ 0x001120A8 (0x28 bytes)
 *   addiu sp,sp,-0x10
 *   addiu v0,zero,0x1
 *   bne   a0,v0,.L001120C0
 *    sd   ra,0x0(sp)
 *   jal   func_001101D8
 *    daddu a0,a1,zero
 * .L001120C0:
 *   ld ra,0(sp); daddu v0,zero,zero; jr ra; addiu sp,sp,0x10
 * If the first argument is 1, call func_001101D8 with the second; return 0.
 */
extern int Exit();

int kill(int a0, int a1) {
    if (a0 == 1)
        Exit(a1);
    return 0;
}
