/* asm/cod/007260.s -> FlushCache @ 0x00107260 (0x10 bytes)
 * SCE libkernl syscall 0x64 (FlushCache) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int FlushCache(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x64
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
