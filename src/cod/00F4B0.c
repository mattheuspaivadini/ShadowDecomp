/* asm/cod/00F4B0.s -> func_0010F4B0 @ 0x0010F4B0 (0x10 bytes)
 * Syscall 0x56 (_SetTLBEntry) trampoline used by SetTLBEntry (00F4C0.c) and InitTLB32MB (00F590.c).
 * MATCHED. */
int func_0010F4B0(unsigned int index, unsigned int PageMask, unsigned int EntryHi, unsigned int EntryLo0, unsigned int EntryLo1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x56\n\tsyscall" : "=r" (v0) : "r" (index), "r" (PageMask), "r" (EntryHi), "r" (EntryLo0), "r" (EntryLo1) : "$3");
    return v0;
}
