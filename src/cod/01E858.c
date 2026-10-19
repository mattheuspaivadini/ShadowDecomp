/* asm/cod/01E858.s -> func_0011E858.
 * libmc FAT: set an entry's modified time from a BCD sceCdCLOCK (static inline BCD helper; macro form misallocates the year)
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

extern char D_00138CF0[];

int func_0011C8B0(int unit, struct SceMcDirEntry *entry, int a2, int a3);
int func_00128E6C(const char *a, const char *b);   /* strcmp */
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);

static __inline__ int BCD(unsigned char x) { return (x >> 4) * 10 + (x & 0xF); }

int func_0011E858(int unit, int path, sceCdCLOCK *clk) {
    struct SceMcDirEntry entry;
    struct SceMcDirEntry parent;
    int ret;

    ret = func_0011C8B0(unit, &parent, path, 0);
    if (ret != 0)
        return ret;
    if (func_00128E6C(parent.name, D_00138CF0) != 0)
        return 0x81019002;
    ret = func_0011C8B0(unit, &entry, parent.cluster, parent.dir_entry);
    if (ret != 0)
        return ret;
    entry.modified.year = BCD(clk->year) + 2000;
    entry.modified.month = BCD(clk->month);
    entry.modified.day = BCD(clk->day);
    entry.modified.hour = BCD(clk->hour);
    entry.modified.min = BCD(clk->minute);
    entry.modified.sec = BCD(clk->second);
    return func_0011E0B0(unit, &entry, parent.cluster, parent.dir_entry);
}
