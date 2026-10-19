/* asm/cod/020068.s -> _sceMcFatSetAttr.
 * libmc FAT set attributes: resolve path, mask mode (0xE7F0 | attr & 0x180F), stamp modified time from the card clock (inline BCD as 01E858), flush
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
    int cluster;                /* 0x10 */
    int dir_entry;              /* 0x14 */
    sceMcStDateTime modified;   /* 0x18 */
    int attr;                   /* 0x20 */
    int pad24[7];
    char name[32];              /* 0x40 */
    char pad60[0x200 - 0x60];
};

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int _sceMcCoreReadClock(int port, sceCdCLOCK *clk);
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);
int _sceMcpFlushCache(int unit);

static __inline__ int BCD(unsigned char x) { return (x >> 4) * 10 + (x & 0xF); }

int _sceMcFatSetAttr(int unit, const char *name, unsigned short attr) {
    char path[0x80];
    struct SceMcDirEntry entry;
    sceCdCLOCK clk;
    int cluster;
    int dir_entry;
    int ret;

    ret = func_0011D8E0(unit);
    if (ret != 0)
        return ret;
    ret = func_0011D988(unit, name, path);
    if (ret != 0)
        return ret;
    ret = func_0011DC60(unit, path, &entry, &cluster, &dir_entry);
    if (ret != (int)0x81010011)
        return ret;
    if (!(entry.mode & 0x20))
        return 0x81010014;
    entry.mode = (entry.mode & 0xE7F0) | (attr & 0x180F);
    _sceMcCoreReadClock(unit, &clk);
    entry.modified.year = BCD(clk.year) + 2000;
    entry.modified.month = BCD(clk.month);
    entry.modified.day = BCD(clk.day);
    entry.modified.hour = BCD(clk.hour);
    entry.modified.min = BCD(clk.minute);
    entry.modified.sec = BCD(clk.second);
    ret = func_0011E0B0(unit, &entry, cluster, dir_entry);
    if (ret != 0)
        return ret;
    if (_sceMcpFlushCache(unit) != 0)
        return 0;
    return 0x8101006F;
}
