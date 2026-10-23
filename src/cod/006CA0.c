/* asm/cod/006CA0.s -> SetVCommonHandler @ 0x00106CA0 (0x10 bytes)
 * SCE libkernl syscall 0xE (SetVCommonHandler) stub (00F360.c template).
 * caller 00F2D8.c.
 * MATCHED. */
void *SetVCommonHandler(int cause, void *handler) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xE\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler) : "$3");
    return (void *)v0;
}
