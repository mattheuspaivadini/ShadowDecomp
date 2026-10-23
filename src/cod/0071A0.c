/* asm/cod/0071A0.s -> EnableIntcHandler @ 0x001071A0 (0x10 bytes)
 * SCE libkernl syscall 0x5C (EnableIntcHandler) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int EnableIntcHandler(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5C
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
