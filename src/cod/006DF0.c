/* asm/cod/006DF0.s -> DeleteThread @ 0x00106DF0 (0x10 bytes)
 * SCE libkernl syscall 0x21 (DeleteThread) stub (00F360.c template).
 * callers 002608.c, 002B68.c, 002BD8.c.
 * MATCHED. */
int DeleteThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x21\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
