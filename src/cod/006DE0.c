/* asm/cod/006DE0.s -> CreateThread @ 0x00106DE0 (0x10 bytes)
 * SCE libkernl syscall 0x20 (CreateThread) stub (00F360.c template).
 * callers 001D90.c, 004F60.c, 007768.c.
 * MATCHED. */
int CreateThread(void *param) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x20\n\tsyscall" : "=r" (v0) : "r" (param) : "$3");
    return v0;
}
