/* asm/cod/007310.s -> iGsGetIMR @ 0x00107310 (0x10 bytes)
 * SCE libkernl syscall -0x70 (iGsGetIMR) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iGsGetIMR(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x70
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
