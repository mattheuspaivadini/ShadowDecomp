/* asm/cod/006E60.s -> EnableDispatchThread @ 0x00106E60 (0x10 bytes)
 * SCE libkernl syscall 0x28 (EnableDispatchThread) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
void EnableDispatchThread(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x28\n\tsyscall" : : : "$3");
}
