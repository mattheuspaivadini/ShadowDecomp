/* asm/cod/006D40.s -> _EnableDmac @ 0x00106D40 (0x10 bytes)
 * SCE libkernl syscall 0x16 (_EnableDmac) stub (00F360.c template).
 * caller EnableDmac (0075A8.c).
 * MATCHED. */
int _EnableDmac(int channel) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x16\n\tsyscall" : "=r" (v0) : "r" (channel) : "$3");
    return v0;
}
