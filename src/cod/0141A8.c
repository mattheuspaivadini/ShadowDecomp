/* asm/cod/0141A8.s -> func_001141A8 @ 0x001141A8 (0x10 bytes)
 * Syscall 0x80 (GsGetCRTOffset) trampoline used by sceGsSetDefDispEnv (0141B8.c).
 * MATCHED. */
void func_001141A8(int mode, int *a, int *b, int *c, int *d) {
    __asm__ __volatile__ ("addiu $3, $0, 0x80\n\tsyscall" : : "r" (mode), "r" (a), "r" (b), "r" (c), "r" (d) : "$3");
}
