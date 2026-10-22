/* asm/cod/00FE30.s -> func_0010FE30 @ 0x0010FE30 (0x10 bytes)
 * Syscall 0x74 (SetSyscall) trampoline used by InitExecPS2 (00FF00.c).
 * MATCHED. */
void func_0010FE30(int a0, int a1) {
    __asm__ __volatile__ ("addiu $3, $0, 0x74\n\tsyscall" : : "r" (a0), "r" (a1) : "$3");
}
