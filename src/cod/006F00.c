/* asm/cod/006F00.s -> SleepThread @ 0x00106F00 (0x10 bytes)
 * SCE libkernl syscall 0x32 (SleepThread) stub (00F360.c template).
 * callers 000A58.c, 001A50.c, 0039C0.c.
 * MATCHED. */
int SleepThread(void) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x32\n\tsyscall" : "=r" (v0) : : "$3");
    return v0;
}
