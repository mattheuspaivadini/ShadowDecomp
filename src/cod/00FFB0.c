/* asm/cod/00FFB0.s -> func_0010FFB0 @ 0x0010FFB0 (0x10 bytes)
 * Syscall 0x5A (Setupee) trampoline used by func_00110000 (010000.c).
 * MATCHED. */
int func_0010FFB0(void *dst, void *src, int n) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x5A\n\tsyscall" : "=r" (v0) : "r" (dst), "r" (src), "r" (n) : "$3");
    return v0;
}
