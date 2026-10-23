/* asm/cod/007160.s -> RFU088_iPollEvnetFlag @ 0x00107160 (0x10 bytes)
 * SCE libkernl syscall -0x58 (RFU088_iPollEvnetFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU088_iPollEvnetFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x58
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
