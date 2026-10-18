/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 7 [cc=29] (was 25).
 * ExecPS2 argv packer: kernel arg slots + strings after slot+0x40, int-returning copy helpers (free v0), argc clamped to 15. Residual = &D_00133168 materialised in v0 and copied to a3 (original builds it straight into a3) plus the end/argv save order (permute_gen --pairs 800 + permute_types --locals 86: no gain).
 * The original .s stays in the build (asm/cod/010000.s); this C
 * draft (Session 23) is kept for the record. */
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
    end = (char *)slot + 0x40;
    ptr = end;
    func_0010FFF0(D_00133168[0], D_00133168[1], argv, D_00133168);
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
