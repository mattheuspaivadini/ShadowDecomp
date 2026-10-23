/* asm/cod/006E10.s -> ExitThread @ 0x00106E10 (0x10 bytes)
 * SCE libkernl syscall 0x23 (ExitThread) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
void ExitThread(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x23\n\tsyscall" : : : "$3");
}
