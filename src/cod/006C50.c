/* asm/cod/006C50.s -> RFU009 @ 0x00106C50 (0x10 bytes)
 * SCE libkernl syscall 0x9 (RFU009) stub (00F360.c template).
 * UNCONFIRMED: reserved slot, no caller; prototype unknown (no arguments assumed).
 * MATCHED. */
void RFU009(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x9\n\tsyscall" : :  : "$3");
}
