/* asm/cod/006E90.s -> RotateThreadReadyQueue @ 0x00106E90 (0x10 bytes)
 * SCE libkernl syscall 0x2B (RotateThreadReadyQueue) stub (00F360.c template).
 * caller 007690.c.
 * MATCHED. */
int RotateThreadReadyQueue(int prio) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x2B\n\tsyscall" : "=r" (v0) : "r" (prio) : "$3");
    return v0;
}
