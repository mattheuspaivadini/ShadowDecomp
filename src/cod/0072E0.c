/* asm/cod/0072E0.s -> SetOsdConfigParam2 @ 0x001072E0 (0x10 bytes)
 * SCE libkernl syscall 0x6E (SetOsdConfigParam2) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetOsdConfigParam2(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x6E
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
