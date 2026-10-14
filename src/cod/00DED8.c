/* asm/cod/00DED8.s -> func_0010DED8 @ 0x0010DED8 (0x1C bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_0010DE60
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and fall through to the epilogue (no sibling call).
 */
extern void func_0010DE60();

void func_0010DED8(void) {
    func_0010DE60();
}
