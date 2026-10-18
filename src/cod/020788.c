/* asm/cod/020788.s -> _sceMcpFlushCache.
 * _sceMcpFlushCache; r = 1 default + struct index (Session 23)
 * MATCHED. */
struct C { int clust; int p4; int p8; int fC; char buf[0x2000]; };
extern struct C D_0015F480[];
int _sceMcpWriteClust(int index, void *buf, int a2, int a3);
int _sceMcpFlushCache(int i) {
    int r = 1;
    if (D_0015F480[i].clust != -1) {
        r = _sceMcpWriteClust(i, D_0015F480[i].buf, D_0015F480[i].clust, D_0015F480[i].fC);
        D_0015F480[i].clust = -1;
        D_0015F480[i].fC = 0;
    }
    return r;
}
