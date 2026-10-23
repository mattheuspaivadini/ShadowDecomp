/* asm/cod/00FE40.s -> func_0010FE40 @ 0x0010FE40 (0x10 bytes)
 * Syscall 0x5A (Setupee) trampoline used by InitExecPS2 (00FF00.c).
 * MATCHED. */
void func_0010FE40(int a0, int *a1, int a2) {
    __asm__ __volatile__ ("addiu $3, $0, 0x5A\n\tsyscall" : : "r" (a0), "r" (a1), "r" (a2) : "$3");
}
