/* asm/cod/006FA0.s -> RFU060 @ 0x00106FA0 (0x10 bytes)
 * SCE libkernl syscall 0x3C (RFU060) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU060(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x3C
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
