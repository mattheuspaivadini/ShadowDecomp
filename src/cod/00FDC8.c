/* asm/cod/00FDC8.s -> func_0010FDC8 @ 0x0010FDC8 (0x10 bytes)
 * Syscall 0x74 (SetSyscall) trampoline used by func_0010FCC8 (00FCC8.c).
 * MATCHED. */
int func_0010FDC8(int a0, int a1) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x74\n\tsyscall" : "=r" (v0) : "r" (a0), "r" (a1) : "$3");
    return v0;
}
