/* asm/cod/007240.s -> DisableCache @ 0x00107240 (0x10 bytes)
 * SCE libkernl syscall 0x62 (DisableCache) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int DisableCache(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x62
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
