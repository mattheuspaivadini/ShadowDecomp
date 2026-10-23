/* asm/cod/006CC0.s -> AddIntcHandler @ 0x00106CC0 (0x10 bytes)
 * SCE libkernl syscall 0x10 (AddIntcHandler) stub (00F360.c template).
 * MATCHED. */
int AddIntcHandler(int cause, void *handler, int next) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x10\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler), "r" (next) : "$3");
    return v0;
}
