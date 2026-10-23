/* asm/cod/006E20.s -> ExitDeleteThread @ 0x00106E20 (0x10 bytes)
 * SCE libkernl syscall 0x24 (ExitDeleteThread) stub (00F360.c template).
 * callers 001CC8.c, 016D88.c.
 * MATCHED. */
void ExitDeleteThread(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x24\n\tsyscall" : : : "$3");
}
