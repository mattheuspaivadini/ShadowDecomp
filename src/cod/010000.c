/* asm/cod/010000.s -> func_00110000.
 * ExecPS2 argv packer; a3-pinned D_00133168, empty asm on the end copy (Session 42)
 * MATCHED. */
extern int _kExecArg[];
extern int D_00133168[];
int func_0010FFF0(int a0, int a1, char **argv, int *p);
int func_0010FFB0(void *dst, void *src, int n);
int func_001290C4(const char *s);   /* strlen */

char *func_00110000(char *name, int argc, char **argv) {
    char *ptr;
    char **slot;
    char *end;
    int n;
    int i;

    slot = (char **)_kExecArg[0];
    ptr = (char *)slot + 0x40;
    end = ptr;
    asm("" : "+r"(end));    /* end gets its own copy before the parameter saves */
    { register int *d asm("$7") = D_00133168;
    func_0010FFF0(d[0], d[1], argv, d); }
    if (argc >= 0x10)
        argc = 0xF;
    func_0010FFB0(slot, &ptr, 4);
    slot++;
    n = func_001290C4(name) + 1;
    func_0010FFB0(ptr, name, n);
    ptr += n;
    for (i = 0; i < argc; i++) {
        func_0010FFB0(slot, &ptr, 4);
        slot++;
        n = func_001290C4(argv[i]) + 1;
        func_0010FFB0(ptr, argv[i], n);
        ptr += n;
    }
    return end;
}
