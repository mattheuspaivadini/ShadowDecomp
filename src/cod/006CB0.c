/* asm/cod/006CB0.s -> SetVInterruptHandler @ 0x00106CB0 (0x10 bytes)
 * SCE libkernl syscall 0xF (SetVInterruptHandler) stub (00F360.c template).
 * MATCHED. */
void *SetVInterruptHandler(int cause, void *handler) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xF\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler) : "$3");
    return (void *)v0;
}
