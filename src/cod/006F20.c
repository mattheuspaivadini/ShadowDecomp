/* asm/cod/006F20.s -> _iWakeupThread @ 0x00106F20 (0x10 bytes)
 * SCE libkernl syscall -0x34 (_iWakeupThread) stub (00F360.c template).
 * caller iWakeupThread (007858.c).
 * MATCHED. */
int _iWakeupThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x34\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
