/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/003258.s); this C
 * draft (10) is kept for the record. */
extern char D_00136A20[];              /* lui/%lo - non-small */
extern char D_00136A68[];              /* lui/%lo - non-small */
extern char D_00136AB0[];              /* lui/%lo - non-small */
extern char D_0013CB90[];              /* lui/%lo - non-small */
extern int D_0013A008;                 /* %gp_rel - small scalar */
int func_00102CF8(char *fmt, ...);

void LoaderSysDumpIopModuleIdentifiers(void) {
    char *p = D_0013CB90;
    int i;

    func_00102CF8(D_00136A20);
    func_00102CF8(D_00136A68);
    for (i = 0; i < D_0013A008; i++) {
        func_00102CF8(D_00136AB0, i, p);
        p += 0x10;
    }
    func_00102CF8(D_00136A68);
}
