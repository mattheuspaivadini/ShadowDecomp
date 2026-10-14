/* asm/cod/007630.s -> func_00107630 @ 0x00107630 (0x20 bytes)
 *   call func_00106D90, then `sync`.
 */
extern void func_00106D90();

void func_00107630(void) {
    func_00106D90();
    __asm__ __volatile__("sync" ::: "memory");
}
