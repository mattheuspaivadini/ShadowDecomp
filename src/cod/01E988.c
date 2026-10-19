/* asm/cod/01E988.s -> _sceMcFatSearchFile.
 * Memory-card FAT file lookup filling a file-info record (timestamps, size, attr, name) from the directory entry (Session 28).
 * MATCHED. */
typedef struct {
    unsigned char resv2, sec, min, hour;
    unsigned char day, month;
    unsigned short year;
} sceMcStDateTime;

/* Memory-card FAT directory entry (cf. 020370): mode, length, timestamps, name. */
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
    /* UNCONFIRMED: the frame reserves 0x220 bytes below path[] here but 0x200
     * in _sceMcFatGetEntSpace (020370); the extra 0x20 may be a separate local. */
    char pad60[0x220 - 0x60];
};

struct SceMcFileInfo {
    sceMcStDateTime created;    /* 0x00 */
    sceMcStDateTime modified;   /* 0x08 */
    int size;                   /* 0x10 */
    unsigned short attr;        /* 0x14 */
    unsigned short pad16;
    char name[32];              /* 0x18 */
};

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *name, char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int a3, int a4);
char *func_00128FB0(char *dst, const char *src);   /* strcpy */

int _sceMcFatSearchFile(int unit, const char *name, struct SceMcFileInfo *info) {
    struct SceMcDirEntry entry;
    char path[0x80];
    int ret;

    ret = func_0011D8E0(unit);
    if (ret != 0)
        return ret;
    ret = func_0011D988(unit, name, path);
    if (ret != 0)
        return ret;
    ret = func_0011DC60(unit, path, &entry, 0, 0);
    if (ret == (int)0x81010011)
        ret = 0;
    if (info != 0 && ret == 0) {
        func_00128FB0(info->name, entry.name);
        info->created = entry.created;
        info->modified = entry.modified;
        info->size = entry.length;
        info->attr = entry.mode;
    }
    return ret;
}
