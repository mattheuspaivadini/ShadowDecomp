/* asm/cod/007070.s -> RFU073 @ 0x00107070 (0x10 bytes)
 * SCE libkernl syscall 0x49 (RFU073) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU073(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x49
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
