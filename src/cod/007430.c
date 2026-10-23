/* asm/cod/007430.s -> MachineType @ 0x00107430 (0x10 bytes)
 * SCE libkernl syscall 0x7E (MachineType) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int MachineType(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x7E
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
