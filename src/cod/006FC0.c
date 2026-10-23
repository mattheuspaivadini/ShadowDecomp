/* asm/cod/006FC0.s -> EndOfHeap @ 0x00106FC0 (0x10 bytes)
 * SCE libkernl syscall 0x3E (EndOfHeap) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int EndOfHeap(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x3E
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
