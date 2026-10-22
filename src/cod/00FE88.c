/* asm/cod/00FE88.s -> func_0010FE88 @ 0x0010FE88 (0x10 bytes)
 * Syscall 0x5B (GetSyscall) trampoline used by InitExecPS2 (00FF00.c).
 * MATCHED. */
int func_0010FE88(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5B\n\tsyscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
