/* asm/cod/00FFF0.s -> func_0010FFF0 @ 0x0010FFF0 (0x10 bytes)
 * Syscall 0x74 (SetSyscall) trampoline used by func_00110000 (010000.c).
 * MATCHED. */
int func_0010FFF0(int a0, int a1, char **argv, int *p) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x74\n\tsyscall" : "=r" (v0) : "r" (a0), "r" (a1), "r" (argv), "r" (p) : "$3");
    return v0;
}
