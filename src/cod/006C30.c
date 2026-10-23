/* asm/cod/006C30.s -> _ExecPS2 @ 0x00106C30 (0x10 bytes)
 * SCE libkernl syscall 0x7 (_ExecPS2) stub (00F360.c template).
 * caller ExecPS2 (010120.c).
 * MATCHED. */
int _ExecPS2(void *entry, void *gp, int argc, char **argv) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0x7\n\tsyscall" : "=r" (v0) : "r" (entry), "r" (gp), "r" (argc), "r" (argv) : "$3");
    return v0;
}
