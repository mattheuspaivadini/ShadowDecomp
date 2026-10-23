/* asm/cod/007270.s -> CpuConfig @ 0x00107270 (0x10 bytes)
 * SCE libkernl syscall 0x66 (CpuConfig) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int CpuConfig(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x66
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
