/* asm/cod/006F90.s -> JoinThread @ 0x00106F90 (0x10 bytes)
 * SCE libkernl syscall 0x3B (JoinThread) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int JoinThread(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x3B
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
