/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 22 [cc=29].
 * R1 wave3d: base+const then +scaled index address build
 * The original .s stays in the build (asm/cod/020788.s); this C
 * draft (Session 8) is kept for the record. */
int _sceMcpWriteClust(int index, int a1, int a2, int a3);

extern char D_0015F480[];   /* .bss table of 0x2010-byte records, lui/%lo */

int _sceMcpFlushCache(int a0) {
    char *p;
    int r;

    p = D_0015F480 + a0 * 0x2010;
    if (*(int *)p == -1)
        return 1;
    r = _sceMcpWriteClust(a0, (int)(p + 0x10), *(int *)p, *(int *)(p + 0xC));
    *(int *)p = -1;
    *(int *)(p + 0xC) = 0;
    return r;
}
