/* asm/cod/007190.s -> RFU091 @ 0x00107190 (0x10 bytes)
 * SCE libkernl syscall 0x5B (RFU091) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU091(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5B
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
