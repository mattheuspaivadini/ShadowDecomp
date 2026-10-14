/* asm/cod/007670.s -> func_00107670 @ 0x00107670 (0x20 bytes)
 *   call func_00106DB0, then `sync`.
 */
extern void func_00106DB0();

void func_00107670(void) {
    func_00106DB0();
    __asm__ __volatile__("sync" ::: "memory");
}
