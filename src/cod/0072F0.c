/* asm/cod/0072F0.s -> GetOsdConfigParam2 @ 0x001072F0 (0x10 bytes)
 * SCE libkernl syscall 0x6F (GetOsdConfigParam2) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int GetOsdConfigParam2(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x6F
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
