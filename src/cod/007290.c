/* asm/cod/007290.s -> iFlushCache @ 0x00107290 (0x10 bytes)
 * SCE libkernl syscall -0x68 (iFlushCache) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int iFlushCache(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x68
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
