/* asm/cod/006D00.s -> AddDmacHandler2 @ 0x00106D00 (0x10 bytes)
 * SCE libkernl syscall 0x12 (AddDmacHandler2) stub (00F360.c template).
 * same syscall as AddDmacHandler, the fourth argument rides in $a3.
 * MATCHED. */
int AddDmacHandler2(int channel, void *handler, int next, void *arg) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x12\n\tsyscall" : "=r" (v0) : "r" (channel), "r" (handler), "r" (next), "r" (arg) : "$3");
    return v0;
}
