/* asm/cod/006C10.s -> RFU005 @ 0x00106C10 (0x10 bytes)
 * SCE libkernl syscall 0x5 (RFU005) stub (00F360.c template).
 * UNCONFIRMED: reserved slot, no caller; prototype unknown (no arguments assumed).
 * MATCHED. */
void RFU005(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x5\n\tsyscall" : :  : "$3");
}
