/* asm/cod/0070C0.s -> SetGsHParam @ 0x001070C0 (0x10 bytes)
 * SCE libkernl syscall 0x4E (SetGsHParam) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetGsHParam(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x4E
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
