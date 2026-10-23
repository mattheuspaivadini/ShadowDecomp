/* asm/cod/006E80.s -> iChangeThreadPriority @ 0x00106E80 (0x10 bytes)
 * SCE libkernl syscall -0x2A (iChangeThreadPriority) stub (00F360.c template).
 * caller 01A600.c.
 * MATCHED. */
int iChangeThreadPriority(int tid, int prio) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x2A\n\tsyscall" : "=r" (v0) : "r" (tid), "r" (prio) : "$3");
    return v0;
}
