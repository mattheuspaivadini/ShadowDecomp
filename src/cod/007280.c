/* asm/cod/007280.s -> iGetCop0 @ 0x00107280 (0x10 bytes)
 * SCE libkernl syscall -0x67 (iGetCop0) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iGetCop0(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x67
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
