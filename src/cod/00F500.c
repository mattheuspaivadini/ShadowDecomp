/* asm/cod/00F500.s -> GetTLBEntry @ 0x0010F500 (0x10 bytes)
 * Syscall 0x57 (GetTLBEntry) trampoline.
 * MATCHED. */
int GetTLBEntry(int index, unsigned int *PageMask, unsigned int *EntryHi, unsigned int *EntryLo0, unsigned int *EntryLo1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x57\n\tsyscall" : "=r" (v0) : "r" (index), "r" (PageMask), "r" (EntryHi), "r" (EntryLo0), "r" (EntryLo1) : "$3");
    return v0;
}
