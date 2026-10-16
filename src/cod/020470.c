/* asm/cod/020470.s -> func_00120470 @ 0x00120470 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001211F8
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int _sceMcCoreGetCardSpec();

int _sceMcpGetCardSpec(void) {
    return _sceMcCoreGetCardSpec();
}
