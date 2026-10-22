/* asm/cod/00F4A0.s -> iPutTLBEntry @ 0x0010F4A0 (0x10 bytes)
 * Syscall -0x55 (iPutTLBEntry) trampoline.
 * MATCHED. */
int iPutTLBEntry(unsigned int PageMask, unsigned int EntryHi, unsigned int EntryLo0, unsigned int EntryLo1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x55\n\tsyscall" : "=r" (v0) : "r" (PageMask), "r" (EntryHi), "r" (EntryLo0), "r" (EntryLo1) : "$3");
    return v0;
}
