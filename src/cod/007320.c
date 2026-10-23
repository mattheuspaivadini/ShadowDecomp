/* asm/cod/007320.s -> GsPutIMR @ 0x00107320 (0x10 bytes)
 * SCE libkernl syscall 0x71 (GsPutIMR) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int GsPutIMR(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x71
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
