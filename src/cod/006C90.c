/* asm/cod/006C90.s -> SetVTLBRefillHandler @ 0x00106C90 (0x10 bytes)
 * SCE libkernl syscall 0xD (SetVTLBRefillHandler) stub (00F360.c template).
 * callers 00F278.c / 00F2D8.c.
 * MATCHED. */
void *SetVTLBRefillHandler(int cause, void *handler) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xD\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler) : "$3");
    return (void *)v0;
}
