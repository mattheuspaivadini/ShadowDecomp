/* asm/cod/020490.s -> func_00120490 @ 0x00120490 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001213D0
 *    nop
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * A plain wrapper: call and return the callee's value.
 */
extern int _sceMcCoreCheckNewCard();

int _sceMcpCheckNewCard(void) {
    return _sceMcCoreCheckNewCard();
}
