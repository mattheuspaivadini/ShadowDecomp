/* asm/cod/006EA0.s -> _iRotateThreadReadyQueue @ 0x00106EA0 (0x10 bytes)
 * SCE libkernl syscall -0x2C (_iRotateThreadReadyQueue) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int _iRotateThreadReadyQueue(int prio) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0x2C\n\tsyscall" : "=r" (v0) : "r" (prio) : "$3");
    return v0;
}
