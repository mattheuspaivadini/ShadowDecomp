/* asm/cod/006BF0.s -> RFU003 @ 0x00106BF0 (0x10 bytes)
 * SCE libkernl syscall 0x3 (RFU003) stub (00F360.c template).
 * UNCONFIRMED: reserved slot, no caller; prototype unknown (no arguments assumed).
 * MATCHED. */
void RFU003(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x3\n\tsyscall" : :  : "$3");
}
