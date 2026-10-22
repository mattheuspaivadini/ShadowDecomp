/* asm/cod/00F510.s -> iGetTLBEntry @ 0x0010F510 (0x10 bytes)
 * Syscall -0x57 (iGetTLBEntry) trampoline.
 * MATCHED. */
int iGetTLBEntry(int index, unsigned int *PageMask, unsigned int *EntryHi, unsigned int *EntryLo0, unsigned int *EntryLo1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x57\n\tsyscall" : "=r" (v0) : "r" (index), "r" (PageMask), "r" (EntryHi), "r" (EntryLo0), "r" (EntryLo1) : "$3");
    return v0;
}
