/* asm/cod/022358.s -> func_00122358 @ 0x00122358 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_001232F0
 *    addiu a0,zero,0x1
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * Wrapper that calls with a constant first argument.
 */
extern void func_001232F0();

void func_00122358(void) {
    func_001232F0(1);
}
