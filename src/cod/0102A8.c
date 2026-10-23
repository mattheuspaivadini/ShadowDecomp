/* asm/cod/0102A8.s -> func_001102A8 @ 0x001102A8 (0x10 bytes)
 * Syscall 0x5B (GetSyscall) trampoline used by InitAlarm (0102B8.c).
 * MATCHED. */
int func_001102A8(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5B\n\tsyscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
