/* asm/cod/006D10.s -> RemoveDmacHandler @ 0x00106D10 (0x10 bytes)
 * SCE libkernl syscall 0x13 (RemoveDmacHandler) stub (00F360.c template).
 * caller 012B98.c.
 * MATCHED. */
int RemoveDmacHandler(int channel, int handler_id) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x13\n\tsyscall" : "=r" (v0) : "r" (channel), "r" (handler_id) : "$3");
    return v0;
}
