/* asm/cod/006E50.s -> DisableDispatchThread @ 0x00106E50 (0x10 bytes)
 * SCE libkernl syscall 0x27 (DisableDispatchThread) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
void DisableDispatchThread(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x27\n\tsyscall" : : : "$3");
}
