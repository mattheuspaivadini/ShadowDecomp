/* asm/cod/00FBF8.s -> func_0010FBF8 @ 0x0010FBF8 (0x10 bytes)
 * Syscall 0x5A (Setupee) trampoline used by GetSystemCallEntry (00FC90.c).
 * MATCHED. */
int func_0010FBF8(int *dst, int *src, int n) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5A\n\tsyscall" : "=r" (v0) : "r" (dst), "r" (src), "r" (n) : "$3");
    return v0;
}
