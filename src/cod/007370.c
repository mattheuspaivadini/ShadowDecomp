/* asm/cod/007370.s -> _print @ 0x00107370 (0x10 bytes)
 * SCE libkernl syscall 0x75 (_print) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int _print(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x75
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
