/* asm/cod/006F10.s -> WakeupThread @ 0x00106F10 (0x10 bytes)
 * SCE libkernl syscall 0x33 (WakeupThread) stub (00F360.c template).
 * callers 000A58.c, 001A50.c, 007690.c.
 * MATCHED. */
int WakeupThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x33\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
