/* asm/cod/01F7F0.s -> _sceMcFatDeleteFile.
 * _sceMcFatDeleteFile; unsigned cluster chain walk, sign test written as & 0x80000000 so the xor constant is shared (Session 35)
 * MATCHED. */
typedef struct {
    unsigned char resv2, sec, min, hour;
    unsigned char day, month;
    unsigned short year;
} sceMcStDateTime;

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

struct F { char pad00[0x800]; int f800; int f804; char path[0x80]; int f888; int f88C; int f890; int f894; };
extern struct F D_0015DF48[];
extern char D_00138D60[];

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);
int _sceMcpFlushCache(int unit);
char *func_00128FB0(char *dst, const char *src);   /* strcpy */
char *func_00128BB0(char *dst, const char *src);   /* strcat */
int _sceMcFatGetDir(int unit, char *name, int a, int b, int c, int *count);
unsigned int func_0011C4C8(int unit, unsigned int clust, int *err);
int func_0011C578(int unit, int clust, int value, int *err);
int func_0011C320(int unit);

int _sceMcFatDeleteFile(int unit, const char *name)
{
    struct SceMcDirEntry entry;
    int resv[4];                /* UNCONFIRMED: unused 16-byte local; the frame has it between entry and path */
    char path[0x80];
    char dir[0x80];
    int cluster;
    int dir_entry;
    int count;
    int ret;
    unsigned int clust, next;

    ret = func_0011D8E0(unit);
    if (ret != 0)
        return ret;
    ret = func_0011D988(unit, name, path);
    if (ret != 0)
        return ret;
    ret = func_0011DC60(unit, path, &entry, &cluster, &dir_entry);
    if (ret != (int)0x81010011)
        return ret;
    if (!(entry.mode & 2))
        return 0x8101000D;
    if (entry.mode & 0x20) {
        func_00128FB0(dir, path);
        func_00128BB0(dir, D_00138D60);
        ret = _sceMcFatGetDir(unit, dir, 0, -1, 0, &count);
        if (ret != 0)
            return ret;
        if (count >= 3)
            return 0x8101005A;
    }
    entry.mode ^= 0x8000;
    ret = func_0011E0B0(unit, &entry, cluster, dir_entry);
    if (ret != 0)
        return ret;
    if (_sceMcpFlushCache(unit) == 0)
        return 0x8101006F;
    if ((unsigned int)entry.cluster == 0xFFFFFFFF)
        return 0;
    next = entry.cluster;
    for (;;) {
        clust = next;
        next = func_0011C4C8(unit, clust, &ret);
        if (ret != 0)
            return ret;
        if (next == 0xFFFFFFFD || !(next & 0x80000000))
            break;
        func_0011C578(unit, clust, next ^ 0x80000000, &ret);
        if (ret != 0)
            return ret;
        if (next == 0xFFFFFFFF)
            break;
        next &= 0x7FFFFFFF;
    }
    if (func_0011C320(unit) == 0 || _sceMcpFlushCache(unit) == 0)
        return 0x8101006F;
    D_0015DF48[unit].f890 = 0;
    return 0;
}
