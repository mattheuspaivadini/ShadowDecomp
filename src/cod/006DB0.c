/* asm/cod/006DB0.s -> _iDisableDmac @ 0x00106DB0 (0x10 bytes)
 * SCE libkernl syscall -0x1D (_iDisableDmac) stub (00F360.c template).
 * caller iDisableDmac (007670.c) forwards $a0 untouched.
 * MATCHED. */
int _iDisableDmac(int channel) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x1D\n\tsyscall" : "=r" (v0) : "r" (channel) : "$3");
    return v0;
}
