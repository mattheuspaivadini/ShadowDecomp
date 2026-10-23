/* asm/cod/006D20.s -> _EnableIntc @ 0x00106D20 (0x10 bytes)
 * SCE libkernl syscall 0x14 (_EnableIntc) stub (00F360.c template).
 * caller EnableIntc (0074D8.c).
 * MATCHED. */
int _EnableIntc(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x14\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
