/* asm/cod/01FB48.s -> _sceMcFatGetDir.
 * _sceMcFatGetDir; entries indexed as buffer[i] (two strength-reduced givs), nested filters with the skip count in the else arm, loop condition !done && length (Session 36)
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

struct McDirTbl {               /* 0x38-byte records filled for the caller */
    sceMcStDateTime created;    /* 0x00 */
    sceMcStDateTime modified;   /* 0x08 */
    int size;                   /* 0x10 */
    unsigned short attr;        /* 0x14 */
    unsigned short pad16;
    char name[32];              /* 0x18 */
};

struct McpCache {
    int table[0x200];
    int unk800;
    int cached_idx;
    unsigned char pad808[0x88C - 0x808];
    int formatted;              /* 0x88C UNCONFIRMED: non-zero once the card FAT is usable */
    unsigned char pad890[0x898 - 0x890];
};

extern struct McpCache D_0015DF48[];
extern char D_0015F080[];
extern char D_00138D08[];       /* "/" */
extern char D_00138CF0[];       /* "." */
extern char D_00138CF8[];       /* ".." */

int _sceMcCoreGetConnection(int port);
int func_0011BFB0(int unit, const char *name, char *path);
int func_00128E6C(const char *a, const char *b);   /* strcmp */
char *func_00128FB0(char *dst, const char *src);   /* strcpy */
char *func_00129578(const char *s, int c);         /* strrchr */
int func_001290C4(const char *s);                  /* strlen */
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry);
int func_0011C8B0(int unit, struct SceMcDirEntry *entry, int cluster, int index);
int func_0011C510(int unit, int clust, int *err);
int _sceMcpReadUserClust(int unit, void *buf, int clust, int count);
int func_0011BCC8(const char *name, const char *pattern);

int _sceMcFatGetDir(int unit, const char *name, int start, int maxent, struct McDirTbl *table, int *count) {
    char path[0x80];
    char dir[0x80];
    char pattern[0x40];
    struct SceMcDirEntry ent;
    struct SceMcDirEntry dent;
    int err;
    int done;
    int isroot;
    int clust;
    int n;
    int i;

    done = 0;
    if (_sceMcCoreGetConnection(unit) == 0)
        return 0x81010013;
    if (D_0015DF48[unit].formatted == 0)
        return 0x8101006F;
    if (func_0011BFB0(unit, name, path) == 0 || func_00128E6C(path, D_00138D08) == 0)
        return 0x81010016;
    func_00128FB0(dir, path);
    *func_00129578(dir, '/') = 0;
    func_00128FB0(pattern, &dir[func_001290C4(dir) + 1]);
    if (func_001290C4(dir) == 0) {
        isroot = 1;
        if ((err = func_0011DC60(unit, D_00138D08, &dent, 0, 0)) != (int)0x81010011)
            return err;
    } else {
        isroot = 0;
        if ((err = func_0011DC60(unit, dir, &dent, 0, 0)) != (int)0x81010011)
            return err;
    }
    if (!(dent.mode & 0x20))
        return 0x81010014;
    if ((err = func_0011C8B0(unit, &ent, dent.cluster, 0)) == 0) {
        if (!(ent.mode & 0x8000) || func_00128E6C(ent.name, D_00138CF0) != 0)
            return 0x81019002;
        err = func_0011C8B0(unit, &ent, dent.cluster, 1);
    }
    if (err != 0) {
        if (err == (int)0x81010002)
            err = 0x81019002;
        return err;
    }
    if (!(ent.mode & 0x8000) || func_00128E6C(ent.name, D_00138CF8) != 0 || dent.length < 2)
        return 0x81019002;
    n = 0;
    if (!(start < dent.length)) {
        if (count != 0)
            *count = 0;
        return 0;
    }
    clust = dent.cluster;
    if (isroot) {
        dent.length -= 2;
        if (dent.length == 0) {
            if (count != 0)
                *count = 0;
            return 0;
        }
        clust = func_0011C510(unit, clust, &err);
        if (err == (int)0x81010059)
            return 0x81019002;
        if (err != 0)
            return err;
    }
    while (!done && dent.length != 0) {
        if (_sceMcpReadUserClust(unit, D_0015F080, clust, 1) == 0)
            return 0x8101006F;
        for (i = 0; i < 2; i++) {
            ent = ((struct SceMcDirEntry *)D_0015F080)[i];
            ent.name[31] = 0;
            if (ent.mode & 0x8000) {
                if (!(ent.mode & 0x2000)) {
                    if (func_0011BCC8(ent.name, pattern) == 1) {
                        if (start == 0) {
                            if (table != 0 && maxent > 0) {
                                table->created = ent.created;
                                table->modified = ent.modified;
                                table->size = ent.length;
                                table->attr = ent.mode;
                                func_00128FB0(table->name, ent.name);
                                if (func_00128E6C(ent.name, D_00138CF0) == 0)
                                    table->attr = dent.mode;
                                func_00128E6C(ent.name, D_00138CF8);
                                table++;
                            }
                            n++;
                            if (maxent > 0 && n >= maxent) {
                                done = 1;
                                break;
                            }
                        } else {
                            start--;
                        }
                    }
                }
            }
            if (--dent.length == 0) {
                done = 1;
                break;
            }
        }
        if (done == 1)
            break;
        clust = func_0011C510(unit, clust, &err);
        if (err == (int)0x81010059)
            return 0x81019002;
        if (err != 0)
            return err;
    }
    if (count != 0)
        *count = n;
    return 0;
}
