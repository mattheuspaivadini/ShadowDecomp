/* asm/cod/00F3A8.s -> func_0010F3A8 @ 0x0010F3A8 (0x10 bytes)
 * Syscall 0x5B (GetSyscall) trampoline used by InitTLBFunctions (00F3C8.c).
 * MATCHED. */
int func_0010F3A8(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5B\n\tsyscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
