/* asm/cod/007150.s -> RFU087_PollEvnetFlag @ 0x00107150 (0x10 bytes)
 * SCE libkernl syscall 0x57 (RFU087_PollEvnetFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU087_PollEvnetFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x57
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
