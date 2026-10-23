/* asm/cod/006FE0.s -> CreateSema @ 0x00106FE0 (0x10 bytes)
 * SCE libkernl syscall 0x40 (CreateSema) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int CreateSema(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x40
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
