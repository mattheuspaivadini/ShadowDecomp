/* asm/cod/007180.s -> RFU090_iReferEventFlagStatus @ 0x00107180 (0x10 bytes)
 * SCE libkernl syscall -0x5A (RFU090_iReferEventFlagStatus) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU090_iReferEventFlagStatus(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x5A
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
