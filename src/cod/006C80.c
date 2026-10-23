/* asm/cod/006C80.s -> Interrupt2Iop @ 0x00106C80 (0x10 bytes)
 * SCE libkernl syscall 0xC (Interrupt2Iop) stub (00F360.c template).
 * MATCHED. */
int Interrupt2Iop(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xC\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
