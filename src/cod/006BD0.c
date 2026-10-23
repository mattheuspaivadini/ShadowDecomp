/* asm/cod/006BD0.s -> ResetEE @ 0x00106BD0 (0x10 bytes)
 * SCE libkernl syscall 0x1 (ResetEE) stub (00F360.c template).
 * MATCHED. */
void ResetEE(int init_bitfield) {
    __asm__ __volatile__ ("addiu $3, $0, 0x1\n\tsyscall" : : "r" (init_bitfield) : "$3");
}
