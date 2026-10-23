/* asm/cod/006D30.s -> _DisableIntc @ 0x00106D30 (0x10 bytes)
 * SCE libkernl syscall 0x15 (_DisableIntc) stub (00F360.c template).
 * caller DisableIntc (007470.c).
 * MATCHED. */
int _DisableIntc(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x15\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
