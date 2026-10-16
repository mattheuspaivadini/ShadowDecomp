/* asm/cod/020CD0.s -> func_00120CD0 @ 0x00120CD0 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_00120B90
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int _sceMcpReadUserClustOnCache();

int _sceMcpReadUserClust(void) {
    return _sceMcpReadUserClustOnCache();
}
