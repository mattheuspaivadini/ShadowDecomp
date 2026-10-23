/* asm/cod/0073C0.s -> sceSifSetDChain @ 0x001073C0 (0x10 bytes)
 * SCE libkernl syscall 0x78 (sceSifSetDChain) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int sceSifSetDChain(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x78
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
