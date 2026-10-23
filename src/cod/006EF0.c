/* asm/cod/006EF0.s -> iReferThreadStatus @ 0x00106EF0 (0x10 bytes)
 * SCE libkernl syscall -0x31 (iReferThreadStatus) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int iReferThreadStatus(int tid, int *status) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x31\n\tsyscall" : "=r" (v0) : "r" (tid), "r" (status) : "$3");
    return v0;
}
