/* asm/cod/007080.s -> SetOsdConfigParam @ 0x00107080 (0x10 bytes)
 * SCE libkernl syscall 0x4A (SetOsdConfigParam) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetOsdConfigParam(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x4A
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
