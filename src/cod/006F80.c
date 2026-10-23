/* asm/cod/006F80.s -> iResumeThread @ 0x00106F80 (0x10 bytes)
 * SCE libkernl syscall -0x3A (iResumeThread) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iResumeThread(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x3A
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
