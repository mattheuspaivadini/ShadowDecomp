/* asm/cod/006D90.s -> _iDisableIntc @ 0x00106D90 (0x10 bytes)
 * SCE libkernl syscall -0x1B (_iDisableIntc) stub (00F360.c template).
 * caller iDisableIntc (007630.c) forwards $a0 untouched.
 * MATCHED. */
int _iDisableIntc(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x1B\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
