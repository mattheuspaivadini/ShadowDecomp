/* asm/cod/007380.s -> sceSifDmaStat @ 0x00107380 (0x10 bytes)
 * SCE libkernl syscall 0x76 (sceSifDmaStat) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int sceSifDmaStat(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x76
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
