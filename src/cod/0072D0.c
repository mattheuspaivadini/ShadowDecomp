/* asm/cod/0072D0.s -> SetCPUTimer @ 0x001072D0 (0x10 bytes)
 * SCE libkernl syscall 0x6D (SetCPUTimer) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetCPUTimer(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x6D
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
