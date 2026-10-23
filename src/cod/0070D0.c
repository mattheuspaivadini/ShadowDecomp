/* asm/cod/0070D0.s -> SetGsVParam @ 0x001070D0 (0x10 bytes)
 * SCE libkernl syscall 0x4F (SetGsVParam) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetGsVParam(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x4F
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
