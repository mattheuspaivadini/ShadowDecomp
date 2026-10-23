/* asm/cod/006FB0.s -> RFU061 @ 0x00106FB0 (0x10 bytes)
 * SCE libkernl syscall 0x3D (RFU061) stub (00F360.c template).
 * UNCONFIRMED: prototype (single int argument assumed; bytes do not depend on it).
 * MATCHED. */
int RFU061(int a0) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x3D
	syscall" : "=r" (v0) : "r" (a0) : "$3");
    return v0;
}
