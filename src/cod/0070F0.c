/* asm/cod/0070F0.s -> RFU081_DeleteEventFlag @ 0x001070F0 (0x10 bytes)
 * SCE libkernl syscall 0x51 (RFU081_DeleteEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU081_DeleteEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x51
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
