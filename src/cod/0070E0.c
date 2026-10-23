/* asm/cod/0070E0.s -> RFU080_CreateEventFlag @ 0x001070E0 (0x10 bytes)
 * SCE libkernl syscall 0x50 (RFU080_CreateEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU080_CreateEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x50
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
