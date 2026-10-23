/* asm/cod/006C60.s -> AddSbusIntcHandler @ 0x00106C60 (0x10 bytes)
 * SCE libkernl syscall 0xA (AddSbusIntcHandler) stub (00F360.c template).
 * MATCHED. */
int AddSbusIntcHandler(int cause, void *handler) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xA\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler) : "$3");
    return v0;
}
