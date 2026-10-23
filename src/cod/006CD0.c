/* asm/cod/006CD0.s -> AddIntcHandler2 @ 0x00106CD0 (0x10 bytes)
 * SCE libkernl syscall 0x10 (AddIntcHandler2) stub (00F360.c template).
 * same syscall as AddIntcHandler, the fourth argument rides in $a3; caller 010430.c.
 * MATCHED. */
int AddIntcHandler2(int cause, void *handler, int next, void *arg) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x10\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler), "r" (next), "r" (arg) : "$3");
    return v0;
}
