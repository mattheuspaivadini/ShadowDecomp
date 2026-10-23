/* asm/cod/006C00.s -> _Exit @ 0x00106C00 (0x10 bytes)
 * SCE libkernl syscall 0x4 (_Exit) stub (00F360.c template).
 * caller Exit (0101D8.c).
 * MATCHED. */
void _Exit(int status) {
    __asm__ __volatile__ ("addiu $3, $0, 0x4\n\tsyscall" : : "r" (status) : "$3");
}
