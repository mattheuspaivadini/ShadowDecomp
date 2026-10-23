/* asm/cod/006E30.s -> TerminateThread @ 0x00106E30 (0x10 bytes)
 * SCE libkernl syscall 0x25 (TerminateThread) stub (00F360.c template).
 * callers 002608.c, 002B68.c, 002BD8.c.
 * MATCHED. */
int TerminateThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x25\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
