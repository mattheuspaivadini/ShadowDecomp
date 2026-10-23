/* asm/cod/007330.s -> iGsPutIMR @ 0x00107330 (0x10 bytes)
 * SCE libkernl syscall -0x71 (iGsPutIMR) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iGsPutIMR(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x71
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
