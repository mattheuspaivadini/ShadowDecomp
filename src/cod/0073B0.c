/* asm/cod/0073B0.s -> isceSifSetDma @ 0x001073B0 (0x10 bytes)
 * SCE libkernl syscall -0x77 (isceSifSetDma) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int isceSifSetDma(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x77
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
