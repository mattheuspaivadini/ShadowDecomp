/* asm/cod/0204B0.s -> func_001204B0 @ 0x001204B0 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001215A8
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int _sceMcCoreAuthentication();

int _sceMcpAuthentication(void) {
    return _sceMcCoreAuthentication();
}
