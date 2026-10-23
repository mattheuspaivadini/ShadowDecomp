/* asm/cod/007420.s -> PSMode @ 0x00107420 (0x10 bytes)
 * SCE libkernl syscall 0x7D (PSMode) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int PSMode(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x7D
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
