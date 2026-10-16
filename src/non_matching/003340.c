/* STATUS (10, 2026-10-16): NON_MATCHING. best score 4 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/003340.s); this C
 * draft (10) is kept for the record. */
struct IopIdentifier {
    char data[16];
};

extern int D_0013A008;          /* .sdata scalar: gp-relative */
extern char D_00136980[];       /* .rodata message: lui/%lo */
extern struct IopIdentifier D_0013CB90[];

int LoaderSysPrintf(char *fmt, ...);
int func_001290C4(char *s);
int func_001293B8(void *dst, char *src, int len);

int setNewIopIdentifier(char *module) {
    int idx;

    LoaderSysPrintf(D_00136980, module, D_0013A008);
    idx = D_0013A008;
    D_0013A008 = idx + 1;
    return func_001293B8(&D_0013CB90[idx], module, func_001290C4(module));
}
