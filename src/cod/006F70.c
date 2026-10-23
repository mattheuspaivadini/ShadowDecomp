/* asm/cod/006F70.s -> ResumeThread @ 0x00106F70 (0x10 bytes)
 * SCE libkernl syscall 0x39 (ResumeThread) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int ResumeThread(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x39
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
