/* asm/cod/006C40.s -> RFU008 @ 0x00106C40 (0x10 bytes)
 * SCE libkernl syscall 0x8 (RFU008) stub (00F360.c template).
 * UNCONFIRMED: reserved slot, no caller; prototype unknown (no arguments assumed).
 * MATCHED. */
void RFU008(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x8\n\tsyscall" : :  : "$3");
}
