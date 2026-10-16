/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 14 [cc=29].
 * R4 w25a_0: two shared -1 return paths
 * The original .s stays in the build (asm/cod/0078F0.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00132280 __attribute__((section(".data")));
extern int  D_00143C90 __attribute__((section(".data")));
extern char D_00143C98[];   /* .data entry table, absolute */

void iSignalSema(int a0);

int iRotateThreadReadyQueue(unsigned int a0) {
    int   n;
    char *p;

    if (a0 >= 0x80)
        return -1;
    if (D_00132280 == 0)
        return -1;
    n = *(int *)(D_00143C98 + 4) & 0x1FF;
    *(int *)(D_00143C98 + 4) = n + 1;
    p = D_00143C98 + n * 2;
    p[8] = 1;
    p[9] = a0;
    iSignalSema(D_00143C90);
    return a0;
}
