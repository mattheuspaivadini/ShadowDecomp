/* asm/cod/020CF0.s -> func_00120CF0 @ 0x00120CF0 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001207F8
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int func_001207F8();

int func_00120CF0(void) {
    return func_001207F8();
}
