/* asm/cod/007450.s -> _InitTLB @ 0x00107450 (0x10 bytes)
 * SCE libkernl syscall 0x82 (_InitTLB) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int _InitTLB(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x82
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
