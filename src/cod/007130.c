/* asm/cod/007130.s -> RFU085_iClearEventFlag @ 0x00107130 (0x10 bytes)
 * SCE libkernl syscall -0x55 (RFU085_iClearEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU085_iClearEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x55
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
