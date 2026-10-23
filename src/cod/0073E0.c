/* asm/cod/0073E0.s -> sceSifSetReg @ 0x001073E0 (0x10 bytes)
 * SCE libkernl syscall 0x79 (sceSifSetReg) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int sceSifSetReg(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x79
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
