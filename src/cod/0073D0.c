/* asm/cod/0073D0.s -> isceSifSetDChain @ 0x001073D0 (0x10 bytes)
 * SCE libkernl syscall -0x78 (isceSifSetDChain) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int isceSifSetDChain(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x78
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
