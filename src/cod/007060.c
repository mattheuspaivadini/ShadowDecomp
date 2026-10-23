/* asm/cod/007060.s -> iReferSemaStatus @ 0x00107060 (0x10 bytes)
 * SCE libkernl syscall -0x48 (iReferSemaStatus) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iReferSemaStatus(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x48
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
