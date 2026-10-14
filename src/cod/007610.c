/* asm/cod/007610.s -> func_00107610 @ 0x00107610 (0x20 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_00106D80
 *    nop
 *   sync
 *   ld ra,0(sp); jr ra; addiu sp,sp,0x10
 * Flush wrapper: call, then fence with `sync`.
 */
extern void func_00106D80();

void func_00107610(void) {
    func_00106D80();
    __asm__ __volatile__("sync" ::: "memory");
}
