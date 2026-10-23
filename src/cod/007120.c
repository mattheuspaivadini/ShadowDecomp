/* asm/cod/007120.s -> RFU084_ClearEventFlag @ 0x00107120 (0x10 bytes)
 * SCE libkernl syscall 0x54 (RFU084_ClearEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU084_ClearEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x54
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
