/* asm/cod/006D80.s -> _iEnableIntc @ 0x00106D80 (0x10 bytes)
 * SCE libkernl syscall -0x1A (_iEnableIntc) stub (00F360.c template).
 * caller iEnableIntc (007610.c) forwards $a0 untouched.
 * MATCHED. */
int _iEnableIntc(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x1A\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
