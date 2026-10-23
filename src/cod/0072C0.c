/* asm/cod/0072C0.s -> SetCPUTimerHandler @ 0x001072C0 (0x10 bytes)
 * SCE libkernl syscall 0x6C (SetCPUTimerHandler) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetCPUTimerHandler(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x6C
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
