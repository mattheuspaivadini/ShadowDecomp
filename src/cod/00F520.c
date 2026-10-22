/* asm/cod/00F520.s -> ProbeTLBEntry @ 0x0010F520 (0x10 bytes)
 * Syscall 0x58 (ProbeTLBEntry) trampoline.
 * MATCHED. */
int ProbeTLBEntry(unsigned int EntryHi, unsigned int *PageMask, unsigned int *EntryLo0, unsigned int *EntryLo1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x58\n\tsyscall" : "=r" (v0) : "r" (EntryHi), "r" (PageMask), "r" (EntryLo0), "r" (EntryLo1) : "$3");
    return v0;
}
