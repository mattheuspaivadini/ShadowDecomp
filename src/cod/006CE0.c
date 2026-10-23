/* asm/cod/006CE0.s -> RemoveIntcHandler @ 0x00106CE0 (0x10 bytes)
 * SCE libkernl syscall 0x11 (RemoveIntcHandler) stub (00F360.c template).
 * callers 002438.c / 010588.c / 013390.c.
 * MATCHED. */
int RemoveIntcHandler(int cause, int handler_id) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x11\n\tsyscall" : "=r" (v0) : "r" (cause), "r" (handler_id) : "$3");
    return v0;
}
