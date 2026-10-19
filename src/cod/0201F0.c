/* asm/cod/0201F0.s -> _sceMcFatRename.
 * libmc FAT rename: build the new path next to the old one, validate the name, require new absent / old present, rewrite the entry name, flush
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

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
char *func_00128CDC(const char *s, int c);      /* strchr */
char *func_00128FB0(char *dst, const char *src); /* strcpy */
char *func_00129578(const char *s, int c);      /* strrchr */
int func_0011BBB8(const char *name);
int func_0011BB48(const char *name);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);
int _sceMcpFlushCache(int unit);

int _sceMcFatRename(int unit, const char *name, const char *newname) {
    struct SceMcDirEntry entry;
    char path[0x80];
    char newpath[0x80];
    int cluster;
    int dir_entry;
    int ret;

    ret = func_0011D8E0(unit);
    if (ret != 0)
        return ret;
    ret = func_0011D988(unit, name, path);
    if (ret != 0)
        return ret;
    if (func_00128CDC(newname, '/') != 0)
        return 0x81010016;
    func_00128FB0(newpath, path);
    func_00128FB0(func_00129578(newpath, '/') + 1, newname);
    if (func_0011BBB8(newname) == 0)
        return 0x81010016;
    if (func_0011BB48(newname) == 0)
        return 0x8101005B;
    ret = func_0011DC60(unit, newpath, &entry, &cluster, &dir_entry);
    if (ret != (int)0x81010002)
        return ret;
    ret = func_0011DC60(unit, path, &entry, &cluster, &dir_entry);
    if (ret != (int)0x81010011)
        return ret;
    func_00128FB0(entry.name, newname);
    ret = func_0011E0B0(unit, &entry, cluster, dir_entry);
    if (ret != 0)
        return ret;
    if (_sceMcpFlushCache(unit) != 0)
        return 0;
    return 0x8101006F;
}
