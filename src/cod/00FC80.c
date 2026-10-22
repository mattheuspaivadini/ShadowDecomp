/* asm/cod/00FC80.s -> func_0010FC80 @ 0x0010FC80 (0x10 bytes)
 * Syscall 0x83 (FindAddress) trampoline used by func_0010FCC8 (00FCC8.c).
 * MATCHED. */
int func_0010FC80(unsigned int a0, unsigned int a1, void (*a2)(void)) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x83\n\tsyscall" : "=r" (v0) : "r" (a0), "r" (a1), "r" (a2) : "$3");
    return v0;
}
