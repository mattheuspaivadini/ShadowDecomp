/* asm/cod/007410.s -> Deci2Call @ 0x00107410 (0x10 bytes)
 * SCE libkernl syscall 0x7C (Deci2Call) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int Deci2Call(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x7C
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
