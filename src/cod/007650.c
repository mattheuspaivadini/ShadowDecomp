/* asm/cod/007650.s -> func_00107650 @ 0x00107650 (0x20 bytes)
 *   call func_00106DA0, then `sync`.
 */
extern void func_00106DA0();

void func_00107650(void) {
    func_00106DA0();
    __asm__ __volatile__("sync" ::: "memory");
}
