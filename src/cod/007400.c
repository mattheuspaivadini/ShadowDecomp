/* asm/cod/007400.s -> _ExecOSD @ 0x00107400 (0x10 bytes)
 * SCE libkernl syscall 0x7B (_ExecOSD) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int _ExecOSD(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x7B
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
