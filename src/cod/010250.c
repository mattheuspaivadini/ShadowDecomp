/* asm/cod/010250.s -> func_00110250 @ 0x00110250 (0x10 bytes)
 * Syscall 0x74 (SetSyscall) trampoline used by InitAlarm (0102B8.c).
 * MATCHED. */
void func_00110250(int a0, int a1) {
    __asm__ __volatile__ ("addiu $3, $0, 0x74\n\tsyscall" : : "r" (a0), "r" (a1) : "$3");
}
