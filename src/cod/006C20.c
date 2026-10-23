/* asm/cod/006C20.s -> _LoadExecPS2 @ 0x00106C20 (0x10 bytes)
 * SCE libkernl syscall 0x6 (_LoadExecPS2) stub (00F360.c template).
 * caller LoadExecPS2 (010190.c).
 * MATCHED. */
void _LoadExecPS2(const char *filename, int argc, char **argv) {
    __asm__ __volatile__ ("addiu $3, $0, 0x6\n\tsyscall" : : "r" (filename), "r" (argc), "r" (argv) : "$3");
}
