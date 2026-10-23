/* asm/cod/006BE0.s -> SetGsCrt @ 0x00106BE0 (0x10 bytes)
 * SCE libkernl syscall 0x2 (SetGsCrt) stub (00F360.c template).
 * sceGsResetGraph (013390.c) declares the arguments short; int here so cc=29 emits no sign extension before the asm (the 0141A8 lever).
 * MATCHED. */
void SetGsCrt(int interlace, int omode, int ffmode) {
    __asm__ __volatile__ ("addiu $3, $0, 0x2\n\tsyscall" : : "r" (interlace), "r" (omode), "r" (ffmode) : "$3");
}
