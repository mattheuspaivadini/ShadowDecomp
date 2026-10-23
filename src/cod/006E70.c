/* asm/cod/006E70.s -> ChangeThreadPriority @ 0x00106E70 (0x10 bytes)
 * SCE libkernl syscall 0x29 (ChangeThreadPriority) stub (00F360.c template).
 * callers 000A58.c, 001A50.c, 0021E0.c.
 * MATCHED. */
int ChangeThreadPriority(int tid, int prio) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x29\n\tsyscall" : "=r" (v0) : "r" (tid), "r" (prio) : "$3");
    return v0;
}
