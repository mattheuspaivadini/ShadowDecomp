/* asm/cod/007350.s -> SetVSyncFlag @ 0x00107350 (0x10 bytes)
 * SCE libkernl syscall 0x73 (SetVSyncFlag) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int SetVSyncFlag(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x73
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
