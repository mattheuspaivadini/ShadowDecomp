/* asm/cod/023180.s -> func_00123180 @ 0x00123180
 * func_00107010(a0); then a `sync` fence and `ei` (enable interrupts). The
 * `sync` idiom is the one used by the matched func_00114020. */
void iSignalSema(int a0);

void func_00123180(int a0) {
    iSignalSema(a0);
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("ei");
}
