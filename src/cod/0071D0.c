/* asm/cod/0071D0.s -> iDisableIntcHandler @ 0x001071D0 (0x10 bytes)
 * SCE libkernl syscall -0x5D (iDisableIntcHandler) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iDisableIntcHandler(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x5D
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
