/* STATUS (Session 35, 2026-10-19): NON_MATCHING. best score 228 [cc=29].
 * libmc FAT create: parent lookup, free-space check, entry init with inline BCD clock, '.' and
 * '..' cluster for directories. The original reads an uninitialised local (s3) in the parent-
 * length test. Residual = isdir and its copy live in s7/s6 (CSE merges ours), count test as movn.
 * Tried: dir copy variable (int/short/char), inline init/enough helpers, int mode.
 * The original .s stays in the build (asm/cod/01EA78.s); this C
 * draft (Session 35) is kept for the record. */
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
    int cluster;                /* 0x10 */
    int dir_entry;              /* 0x14 */
    sceMcStDateTime modified;   /* 0x18 */
    int attr;                   /* 0x20 */
    int pad24[7];
    char name[32];              /* 0x40 */
    char pad60[0x200 - 0x60];
};

struct McName { char s[32]; };

extern struct SceMcDirEntry D_0015F080[2];
extern char D_00138CF0[];   /* "." */
extern char D_00138CF8[];   /* ".." */

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
int func_0011BF68(const char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int func_0011C7D8(int unit, int *err);
int func_0011E258(int unit, int cluster, int length, int *err);
int func_0011C6A8(int unit, int *err);
int func_0011C578(int unit, int clust, int value, int *err);
int _sceMcCoreReadClock(int port, sceCdCLOCK *clk);
void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
char *func_00129578(const char *s, int c);                 /* strrchr */
int func_0011E388(int unit, struct SceMcDirEntry *entry, int cluster, int length, int *err);
int _sceMcpWriteUserClust(int unit, void *buf, int clust, int count);
int func_0011E858(int unit, int cluster, sceCdCLOCK *clk);
int func_0011C320(int unit);
int _sceMcpFlushCache(int unit);

static __inline__ int BCD(unsigned char x) { return (x >> 4) * 10 + (x & 0xF); }

int _sceMcFatCreateFile(int unit, const char *name, unsigned short mode)
{
    struct SceMcDirEntry parent;
    struct SceMcDirEntry ent;
    char path[0x80];
    sceCdCLOCK clk;
    int ret;
    int isdir, top, free, n, clust, idx;
    char *p;

    ret = func_0011D8E0(unit);
    if (ret != 0)
        return ret;
    ret = func_0011D988(unit, name, path);
    if (ret != 0)
        return ret;
    if (mode == 0)
        mode = 0x8417;
    isdir = mode & 0x20;
    if (isdir && func_0011BF68(path) >= 2)
        return 0x81019004;
    top = func_0011BF68(path) == 1;
    ret = func_0011DC60(unit, path, &parent, 0, 0);
    if (ret != (int)0x81010002)
        return ret;
    if (!top && parent.length - n >= 0x14)
        return 0x81010017;
    free = func_0011C7D8(unit, &ret);
    if (ret != 0)
        return ret;
    n = func_0011E258(unit, parent.cluster, parent.length, &ret);
    if (ret != 0)
        return ret;
    if ((n > 0) + free < (isdir ? 2 : 1))
        return 0x8101001C;
    if (isdir) {
        clust = func_0011C6A8(unit, &ret);
        if (ret != 0)
            return ret;
        func_0011C578(unit, clust, -1, &ret);
        if (ret != 0)
            return ret;
    }
    _sceMcCoreReadClock(unit, &clk);
    func_001283D0(&ent, 0, 0x200);
    ent.mode = mode;
    ent.cluster = isdir ? clust : -1;
    ent.length = isdir ? 2 : 0;
    ent.created.year = BCD(clk.year) + 2000;
    ent.created.month = BCD(clk.month);
    ent.created.day = BCD(clk.day);
    ent.created.hour = BCD(clk.hour);
    ent.created.min = BCD(clk.minute);
    ent.created.sec = BCD(clk.second);
    ent.pad02 = 0;
    ent.created.resv2 = 0;
    ent.dir_entry = 0;
    ent.modified = ent.created;
    ent.attr = 0;
    p = func_00129578(path, '/');
    *(struct McName *)ent.name = *(struct McName *)(p + 1);
    idx = func_0011E388(unit, &ent, parent.cluster, parent.length, &ret);
    if (idx < 0)
        return ret;
    if (isdir) {
        func_001283D0(&D_0015F080[0], 0, 0x200);
        D_0015F080[0].mode = 0x8427;
        D_0015F080[0].created.year = BCD(clk.year) + 2000;
        D_0015F080[0].created.month = BCD(clk.month);
        D_0015F080[0].created.day = BCD(clk.day);
        D_0015F080[0].created.hour = BCD(clk.hour);
        D_0015F080[0].created.min = BCD(clk.minute);
        D_0015F080[0].created.sec = BCD(clk.second);
        D_0015F080[0].dir_entry = idx;
        D_0015F080[0].length = 0;
        D_0015F080[0].pad02 = 0;
        D_0015F080[0].cluster = 0;
        D_0015F080[0].modified = D_0015F080[0].created;
        __builtin_memcpy(D_0015F080[0].name, D_00138CF0, 2);
        func_001283D0(&D_0015F080[1], 0, 0x200);
        D_0015F080[1].mode = 0x8427;
        D_0015F080[1].created.year = BCD(clk.year) + 2000;
        D_0015F080[1].created.month = BCD(clk.month);
        D_0015F080[1].created.day = BCD(clk.day);
        D_0015F080[1].created.hour = BCD(clk.hour);
        D_0015F080[1].created.min = BCD(clk.minute);
        D_0015F080[1].created.sec = BCD(clk.second);
        D_0015F080[1].length = 0;
        D_0015F080[1].pad02 = 0;
        D_0015F080[1].created.resv2 = 0;
        D_0015F080[1].cluster = 0;
        D_0015F080[1].dir_entry = 0;
        D_0015F080[1].modified = D_0015F080[1].created;
        D_0015F080[1].attr = 0;
        __builtin_memcpy(D_0015F080[1].name, D_00138CF8, 3);
        if (_sceMcpWriteUserClust(unit, D_0015F080, ent.cluster, 1) == 0)
            return 0x8101006F;
    }
    ret = func_0011E858(unit, parent.cluster, &clk);
    if (ret != 0)
        return ret;
    if (func_0011C320(unit) == 0 || _sceMcpFlushCache(unit) == 0)
        return 0x8101006F;
    return ret;
}
