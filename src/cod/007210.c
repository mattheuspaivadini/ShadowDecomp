/* asm/cod/007210.s -> iDisableDmacHandler @ 0x00107210 (0x10 bytes)
 * SCE libkernl syscall -0x5F (iDisableDmacHandler) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iDisableDmacHandler(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x5F
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
