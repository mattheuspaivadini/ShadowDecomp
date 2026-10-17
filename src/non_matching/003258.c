/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 1 [cc=296].
 * index form fixes the preheader; residual = blez vs blezl: our 2.96 dbr annuls a target-stolen insn when the fall-through call has its arg load in the jal delay (probe build/s19/probe n00 vs a4)
 * The original .s stays in the build (asm/cod/003258.s); this C
 * draft (Session 19) is kept for the record. */
extern char D_00136A20[];              /* lui/%lo - non-small */
extern char D_00136A68[];              /* lui/%lo - non-small */
extern char D_00136AB0[];              /* lui/%lo - non-small */
extern char D_0013CB90[];              /* lui/%lo - non-small */
extern int D_0013A008;                 /* %gp_rel - small scalar */
int LoaderSysPrintf(char *fmt, ...);

void LoaderSysDumpIopModuleIdentifiers(void) {
    int i;

    LoaderSysPrintf(D_00136A20);
    LoaderSysPrintf(D_00136A68);
    for (i = 0; i < D_0013A008; i++)
        LoaderSysPrintf(D_00136AB0, i, D_0013CB90 + i * 0x10);
    LoaderSysPrintf(D_00136A68);
}
