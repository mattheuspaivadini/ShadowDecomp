/* asm/cod/0070B0.s -> GetGsVParam @ 0x001070B0 (0x10 bytes)
 * SCE libkernl syscall 0x4D (GetGsVParam) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int GetGsVParam(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x4D
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
