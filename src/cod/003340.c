/* asm/cod/003340.s -> setNewIopIdentifier.
 * loader (cc=296; SDK prototypes from the image)
 * MATCHED. */
struct IopIdentifier {
    char data[16];
};

extern int D_0013A008;          /* .sdata scalar: gp-relative */
extern char D_00136980[];       /* .rodata message: lui/%lo */
extern struct IopIdentifier D_0013CB90[];

void LoaderSysPrintf(char *fmt, ...);
int func_001290C4(char *s);
int func_001293B8(void *dst, char *src, int len);

int setNewIopIdentifier(char *module) {

    LoaderSysPrintf(D_00136980, module, D_0013A008);
    return func_001293B8(&D_0013CB90[D_0013A008++], module, func_001290C4(module));
}
