/* asm/cod/007220.s -> KSeg0 @ 0x00107220 (0x10 bytes)
 * SCE libkernl syscall 0x60 (KSeg0) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int KSeg0(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x60
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
