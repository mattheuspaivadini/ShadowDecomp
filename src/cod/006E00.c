/* asm/cod/006E00.s -> _StartThread @ 0x00106E00 (0x10 bytes)
 * SCE libkernl syscall 0x22 (_StartThread) stub (00F360.c template).
 * caller StartThread (007AD0.c).
 * MATCHED. */
int _StartThread(int tid, int arg) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x22\n\tsyscall" : "=r" (v0) : "r" (tid), "r" (arg) : "$3");
    return v0;
}
