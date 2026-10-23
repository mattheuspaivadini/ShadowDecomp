/* asm/cod/006EE0.s -> ReferThreadStatus @ 0x00106EE0 (0x10 bytes)
 * SCE libkernl syscall 0x30 (ReferThreadStatus) stub (00F360.c template).
 * caller StartThread (007AD0.c).
 * MATCHED. */
int ReferThreadStatus(int tid, int *status) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x30\n\tsyscall" : "=r" (v0) : "r" (tid), "r" (status) : "$3");
    return v0;
}
