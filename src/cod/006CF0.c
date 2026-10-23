/* asm/cod/006CF0.s -> AddDmacHandler @ 0x00106CF0 (0x10 bytes)
 * SCE libkernl syscall 0x12 (AddDmacHandler) stub (00F360.c template).
 * caller sceSifInitCmd (012918.c).
 * MATCHED. */
int AddDmacHandler(int channel, void *handler, int next) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x12\n\tsyscall" : "=r" (v0) : "r" (channel), "r" (handler), "r" (next) : "$3");
    return v0;
}
