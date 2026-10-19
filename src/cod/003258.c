/* asm/cod/003258.s -> function.
 * LoaderSysPrintf as NOTHROW_STUB (defined earlier in the loader TU): nothrow calls let dbr fill the loop-entry blez plainly, as in the original (Session 28).
 * MATCHED. */
#include "nothrow_stub.h"
extern char D_00136A20[];              /* lui/%lo - non-small */
extern char D_00136A68[];              /* lui/%lo - non-small */
extern char D_00136AB0[];              /* lui/%lo - non-small */
extern char D_0013CB90[];              /* lui/%lo - non-small */
extern int D_0013A008;                 /* %gp_rel - small scalar */
int LoaderSysPrintf(char *fmt, ...);

/* the loader TU defines LoaderSysPrintf before this function (see nothrow_stub.h). */
int NOTHROW_STUB LoaderSysPrintf (char *fmt, ...) { return 0; }

void LoaderSysDumpIopModuleIdentifiers(void) {
    int i;

    LoaderSysPrintf(D_00136A20);
    LoaderSysPrintf(D_00136A68);
    for (i = 0; i < D_0013A008; i++)
        LoaderSysPrintf(D_00136AB0, i, D_0013CB90 + i * 0x10);
    LoaderSysPrintf(D_00136A68);
}
