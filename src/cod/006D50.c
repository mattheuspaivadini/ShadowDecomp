/* asm/cod/006D50.s -> _DisableDmac @ 0x00106D50 (0x10 bytes)
 * SCE libkernl syscall 0x17 (_DisableDmac) stub (00F360.c template).
 * caller DisableDmac (007540.c).
 * MATCHED. */
int _DisableDmac(int channel) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x17\n\tsyscall" : "=r" (v0) : "r" (channel) : "$3");
    return v0;
}
