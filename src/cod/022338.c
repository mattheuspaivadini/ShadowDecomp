/* asm/cod/022338.s -> func_00122338 @ 0x00122338 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001232F0
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int func_001232F0();

int func_00122338(void) {
    return func_001232F0();
}
