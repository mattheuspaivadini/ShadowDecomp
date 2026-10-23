/* asm/cod/007100.s -> RFU082_SetEventFlag @ 0x00107100 (0x10 bytes)
 * SCE libkernl syscall 0x52 (RFU082_SetEventFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU082_SetEventFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x52
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
