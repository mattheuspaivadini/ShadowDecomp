/* asm/cod/006FF0.s -> DeleteSema @ 0x00106FF0 (0x10 bytes)
 * SCE libkernl syscall 0x41 (DeleteSema) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int DeleteSema(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x41
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
