/* asm/cod/00F3B8.s -> func_0010F3B8 @ 0x0010F3B8 (0x10 bytes)
 * Syscall 0x74 (SetSyscall) trampoline used by InitTLBFunctions (00F3C8.c).
 * MATCHED. */
void func_0010F3B8(int a0, int a1) {
    __asm__ __volatile__ ("addiu $3, $0, 0x74\n\tsyscall" : : "r" (a0), "r" (a1) : "$3");
}
