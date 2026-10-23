/* asm/cod/007140.s -> RFU086_WaitEvnetFlag @ 0x00107140 (0x10 bytes)
 * SCE libkernl syscall 0x56 (RFU086_WaitEvnetFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU086_WaitEvnetFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x56
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
