/* asm/cod/00F360.s -> func_0010F360 @ 0x0010F360 (0x10 bytes)
 * Syscall 0x5A (Setupee) trampoline used by InitTLBFunctions (00F3C8.c).
 * MATCHED. */
int func_0010F360(int a0, void *a1, int a2) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5A\n\tsyscall" : "=r" (v0) : "r" (a0), "r" (a1), "r" (a2) : "$3");
    return v0;
}
