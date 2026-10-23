/* asm/cod/006EB0.s -> ReleaseWaitThread @ 0x00106EB0 (0x10 bytes)
 * SCE libkernl syscall 0x2D (ReleaseWaitThread) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int ReleaseWaitThread(int tid) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x2D\n\tsyscall" : "=r" (v0) : "r" (tid) : "$3");
    return v0;
}
