/* asm/cod/007170.s -> RFU089_ReferEventFlagStatus @ 0x00107170 (0x10 bytes)
 * SCE libkernl syscall 0x59 (RFU089_ReferEventFlagStatus) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU089_ReferEventFlagStatus(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x59
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
