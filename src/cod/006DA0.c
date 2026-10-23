/* asm/cod/006DA0.s -> _iEnableDmac @ 0x00106DA0 (0x10 bytes)
 * SCE libkernl syscall -0x1C (_iEnableDmac) stub (00F360.c template).
 * caller iEnableDmac (007650.c) forwards $a0 untouched.
 * MATCHED. */
int _iEnableDmac(int channel) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x1C\n\tsyscall" : "=r" (v0) : "r" (channel) : "$3");
    return v0;
}
