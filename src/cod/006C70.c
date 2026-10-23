/* asm/cod/006C70.s -> RemoveSbusIntcHandler @ 0x00106C70 (0x10 bytes)
 * SCE libkernl syscall 0xB (RemoveSbusIntcHandler) stub (00F360.c template).
 * MATCHED. */
int RemoveSbusIntcHandler(int cause) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xB\n\tsyscall" : "=r" (v0) : "r" (cause) : "$3");
    return v0;
}
