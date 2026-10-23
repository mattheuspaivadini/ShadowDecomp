/* asm/cod/006F40.s -> iCancelWakeupThread @ 0x00106F40 (0x10 bytes)
 * SCE libkernl syscall -0x36 (iCancelWakeupThread) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iCancelWakeupThread(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x36
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
