/* asm/cod/01F210.s -> _sceMcFatWriteFile.
 * _sceMcFatWriteFile; prev = clust right before the next-cluster call, separate mode-test returns, final stamp after the loop break, prev pinned to s4 (Session 36)
 * MATCHED. */
typedef struct {
    unsigned char resv2, sec, min, hour;
    unsigned char day, month;
    unsigned short year;
} sceMcStDateTime;

typedef struct {
    unsigned char stat, second, minute, hour;
    unsigned char pad, day, month, year;
} sceCdCLOCK;

struct SceMcDirEntry {
    unsigned short mode;        /* 0x00 */
    unsigned short pad02;
    int length;                 /* 0x04 */
    sceMcStDateTime created;    /* 0x08 */
    unsigned int cluster;       /* 0x10 */
    int dir_entry;              /* 0x14 */
    sceMcStDateTime modified;   /* 0x18 */
    int attr;                   /* 0x20 */
    int pad24[7];
    char name[32];              /* 0x40 */
    unsigned char f60;                  /* 0x60 UNCONFIRMED: must be 0 for a writable file */
    char pad61[0x200 - 0x61];
};

extern char D_0015F080[];

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int func_0011CA30(int unit, unsigned int clust);
int func_0011C7D8(int unit, int *err);
unsigned int func_0011C6A8(int unit, int *err);
int func_0011C578(int unit, unsigned int clust, int value, int *err);
unsigned int func_0011C4C8(int unit, unsigned int clust, int *err);
int _sceMcCoreReadClock(int port, sceCdCLOCK *clk);
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);
int func_0011E858(int unit, int cluster, sceCdCLOCK *clk);
int func_0011C320(int unit);
int _sceMcpFlushCache(int unit);
int _sceMcpReadUserClust(int unit, void *buf, unsigned int clust, int count);
int _sceMcpWriteUserClust(int unit, void *buf, unsigned int clust, int count);
void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */

static __inline__ int BCD(unsigned char x) { return (x >> 4) * 10 + (x & 0xF); }

int _sceMcFatWriteFile(int unit, const char *name, char *buf, int pos, int size) {
    struct SceMcDirEntry entry;
    char path[0x80];
    sceCdCLOCK clk;
    int cluster;
    int dir_entry;
    int err;
    int err2;
    int total;
    int nclust;
    int have;
    int cur;
    unsigned int clust;
    register unsigned int prev asm("$20");
    char *src;

    if ((err = func_0011D8E0(unit)) != 0)
        return err;
    if ((err = func_0011D988(unit, name, path)) != 0)
        return err;
    err = func_0011DC60(unit, path, &entry, &cluster, &dir_entry);
    if (err != (int)0x81010011)
        return err;
    if (entry.f60 != 0)
        return 0x81019002;
    if ((entry.mode & 0xF000) != 0x8000 && (entry.mode & 0xF000) != 0xA000)
        return 0x81019002;
    if ((entry.mode & 0xF00) != 0x400 && (entry.mode & 0xF00) != 0)
        return 0x81019002;
    if (!(entry.mode & 2))
        return 0x8101000D;
    if (entry.mode & 0x20)
        return 0x81010002;
    if (entry.length < pos)
        return 0x81010016;
    nclust = (pos + size + 0x3FF) / 0x400;
    have = func_0011CA30(unit, entry.cluster);
    if (have < 0)
        return have;
    if (have < nclust) {
        int free = func_0011C7D8(unit, &err);
        if (err != 0)
            return err;
        if (free < nclust - have)
            return 0x8101001C;
    }
    if (entry.cluster == 0xFFFFFFFF) {
        clust = func_0011C6A8(unit, &err);
        if (err != 0)
            return err;
        func_0011C578(unit, clust, -1, &err);
        if (err != 0)
            return err;
        _sceMcCoreReadClock(unit, &clk);
        entry.cluster = clust;
        if (entry.length < cur)     /* cur is not set yet on this path (as in the image) */
            entry.length = cur;
        entry.modified.year = BCD(clk.year) + 2000;
        entry.modified.month = BCD(clk.month);
        entry.modified.day = BCD(clk.day);
        entry.modified.hour = BCD(clk.hour);
        entry.modified.min = BCD(clk.minute);
        entry.modified.sec = BCD(clk.second);
        if ((err = func_0011E0B0(unit, &entry, cluster, dir_entry)) != 0)
            return err;
        if ((err2 = func_0011C320(unit)) == 0)
            return 0x8101006F;
        if ((err2 = _sceMcpFlushCache(unit)) == 0)
            return 0x8101006F;
    }
    total = size;
    clust = entry.cluster;
    cur = pos;
    src = buf;
    while (1) {
        if (pos < 0x400) {
            if (pos > 0 || (pos + size < 0x400 && cur < entry.length)) {
                if ((err2 = _sceMcpReadUserClust(unit, D_0015F080, clust, 1)) == 0)
                    return 0x8101006F;
            }
            if (!(0x400 - pos < size)) {
                func_0012821C(D_0015F080 + pos, src, size);
                if ((err2 = _sceMcpWriteUserClust(unit, D_0015F080, clust, 1)) == 0)
                    return 0x8101006F;
                cur += size;
                _sceMcCoreReadClock(unit, &clk);
                if (entry.length < cur)
                    entry.length = cur;
                break;
            }
            func_0012821C(D_0015F080 + pos, src, 0x400 - pos);
            if ((err2 = _sceMcpWriteUserClust(unit, D_0015F080, clust, 1)) == 0)
                return 0x8101006F;
            cur += 0x400 - pos;
            src += 0x400 - pos;
            size -= 0x400 - pos;
            pos = 0;
        }
        prev = clust;
        clust = func_0011C4C8(unit, prev, &err2);
        if (err2 != 0)
            return err2;
        if (clust == 0xFFFFFFFF) {
            clust = func_0011C6A8(unit, &err);
            if (err != 0)
                return err;
            func_0011C578(unit, clust, -1, &err);
            if (err != 0)
                return err;
            func_0011C578(unit, prev, clust | 0x80000000, &err);
            if (err != 0)
                return err;
        }
        if (pos != 0)
            pos -= 0x400;
        clust &= 0x7FFFFFFF;
    }
    entry.mode |= 0x80;
    entry.modified.year = BCD(clk.year) + 2000;
    entry.modified.month = BCD(clk.month);
    entry.modified.day = BCD(clk.day);
    entry.modified.hour = BCD(clk.hour);
    entry.modified.min = BCD(clk.minute);
    entry.modified.sec = BCD(clk.second);
    if ((err = func_0011E0B0(unit, &entry, cluster, dir_entry)) != 0)
        return err;
    if ((err = func_0011E858(unit, cluster, &clk)) != 0)
        return err;
    if ((err2 = func_0011C320(unit)) == 0)
        return 0x8101006F;
    if ((err2 = _sceMcpFlushCache(unit)) == 0)
        return 0x8101006F;
    return total;
}
