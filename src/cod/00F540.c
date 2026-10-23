/* asm/cod/00F540.s -> ExpandScratchPad @ 0x0010F540 (0x10 bytes)
 * Syscall 0x59 (ExpandScratchPad) trampoline.
 * MATCHED. */
int ExpandScratchPad(unsigned int page) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x59\n\tsyscall" : "=r" (v0) : "r" (page) : "$3");
    return v0;
}
