/* asm/cod/0207F8.s -> _sceMcpWriteUserClustOnCache.
 * libmc2 write-back cache: start, extend (next cluster, under 8, same block) or flush and restart; each path has its own count++ and return, cross-jumped into one tail (Session 34)
 * MATCHED. */
struct McClust { char b[0x400]; };
struct C { int clust; int last; int blk; int count; char buf[0x2000]; };
struct S { char pad00[0x2A]; unsigned short f2A; unsigned short f2C; char pad2E[6]; int f34; char rest[0x184 - 0x38]; };
extern struct C D_0015F480[];
extern struct S gSceMc2SysInfo[];
int _sceMcpFlushCache(int port);

int _sceMcpWriteUserClustOnCache(int port, struct McClust *buf, int clust) {
    struct S *s;
    int blk;
    int r;

    s = &gSceMc2SysInfo[port];
    clust += s->f34;
    blk = clust * s->f2A / s->f2C;
    if (D_0015F480[port].clust == -1) {
        D_0015F480[port].clust = clust;
        D_0015F480[port].last = clust;
        D_0015F480[port].blk = blk;
        D_0015F480[port].count = 0;
        *(struct McClust *)D_0015F480[port].buf = *buf;
        D_0015F480[port].count++;
        return 1;
    }
    if (clust == D_0015F480[port].last + 1 && D_0015F480[port].count < 8
        && D_0015F480[port].blk == blk) {
        D_0015F480[port].last = clust;
        *(struct McClust *)&D_0015F480[port].buf[D_0015F480[port].count * 0x400] = *buf;
        D_0015F480[port].count++;
        return 1;
    }
    r = _sceMcpFlushCache(port);
    D_0015F480[port].clust = clust;
    D_0015F480[port].last = clust;
    D_0015F480[port].blk = blk;
    D_0015F480[port].count = 0;
    *(struct McClust *)D_0015F480[port].buf = *buf;
    D_0015F480[port].count++;
    return r;
}
