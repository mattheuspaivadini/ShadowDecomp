/* asm/cod/006ED0.s -> GetThreadId @ 0x00106ED0 (0x10 bytes)
 * SCE libkernl syscall 0x2F (GetThreadId) stub (00F360.c template).
 * callers 000A58.c, 001A50.c, 001CC8.c.
 * MATCHED. */
int GetThreadId(void) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x2F\n\tsyscall" : "=r" (v0) : : "$3");
    return v0;
}
