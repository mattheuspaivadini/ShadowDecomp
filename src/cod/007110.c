/* asm/cod/007110.s -> RFU083_iSetEventFlag @ 0x00107110 (0x10 bytes)
 * SCE libkernl syscall -0x53 (RFU083_iSetEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU083_iSetEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x53
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
