/* asm/cod/020B90.s -> _sceMcpReadUserClustOnCache.
 * libmc2 cluster read: copy the 0x400-byte cluster from the per-port cache when in range, else _sceMcpReadClust
 * MATCHED. */
struct McClust { char b[0x400]; };
struct C { int clust; int p4; int p8; int fC; char buf[0x2000]; };
struct S { char pad00[0x34]; int f34; char rest[0x184 - 0x38]; };
extern struct C D_0015F480[];
extern struct S gSceMc2SysInfo[];
int _sceMcpReadClust(int port, void *buf, int clust, int count);

int _sceMcpReadUserClustOnCache(int port, struct McClust *buf, int clust) {
    struct S *s;

    s = &gSceMc2SysInfo[port];
    clust += s->f34;
    if (clust >= D_0015F480[port].clust && clust < D_0015F480[port].clust + D_0015F480[port].fC) {
        *buf = *(struct McClust *)&D_0015F480[port].buf[(clust - D_0015F480[port].clust) * 0x400];
        return 1;
    }
    return _sceMcpReadClust(port, buf, clust, 1);
}
