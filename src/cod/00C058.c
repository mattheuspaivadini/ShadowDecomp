/* asm/cod/00C058.s -> func_0010C058 @ 0x0010C058 (0x1C bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal sceStdioCCode
 *    addiu a1,zero,0x6
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * Forwards a0 and passes the constant 6 as the second argument.
 */
extern void sceStdioCCode();

void sceRemove(int a0) {
    sceStdioCCode(a0, 6);
}
