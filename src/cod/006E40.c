/* asm/cod/006E40.s -> iTerminateThread @ 0x00106E40 (0x10 bytes)
 * SCE libkernl syscall -0x26 (iTerminateThread) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int iTerminateThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x26\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
