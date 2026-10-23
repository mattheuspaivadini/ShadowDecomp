/* asm/cod/006BC0.s -> RFU000_FullReset @ 0x00106BC0 (0x10 bytes)
 * SCE libkernl syscall 0x0 (RFU000_FullReset) stub (00F360.c template).
 * UNCONFIRMED: reserved slot, no caller; prototype unknown (no arguments assumed).
 * MATCHED. */
void RFU000_FullReset(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x0\n\tsyscall" : :  : "$3");
}
