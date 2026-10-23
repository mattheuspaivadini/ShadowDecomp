/* asm/cod/0072A0.s -> iCpuConfig @ 0x001072A0 (0x10 bytes)
 * SCE libkernl syscall -0x6A (iCpuConfig) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iCpuConfig(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x6A
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
