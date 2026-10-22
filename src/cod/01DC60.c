/* asm/cod/01DC60.s -> func_0011DC60.
 * libmc FAT path lookup: strtok walk with func_0011D9E8 per component, struct copies to the caller entry, (base + unit)->root index order, bad-entry return as a tail label (Session 35)
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

struct Mc2SysInfo {
    char pad00[0x3C];
    int root;                   /* 0x3C */
    char pad40[0x184 - 0x40];
};

extern struct Mc2SysInfo gSceMc2SysInfo[];
extern char D_00138CF0[];   /* "." */
extern char D_00138D08[];   /* "/" */

int func_0011C8B0(int unit, struct SceMcDirEntry *entry, int clust, int index);
unsigned int func_001290C4(const char *s);                 /* strlen */
int func_00128E6C(const char *a, const char *b);           /* strcmp */
char *func_00128FB0(char *dst, const char *src);           /* strcpy */
char *func_0011BE48(char *s, const char *delim);           /* strtok */
int func_0011D9E8(int unit, struct SceMcDirEntry *out, int *idx, const char *name, int clust, int count);

int func_0011DC60(int unit, char *path, struct SceMcDirEntry *entry, int *cluster, int *dir_entry)
{
    struct SceMcDirEntry cur;
    struct SceMcDirEntry parent;
    char name[0x20];
    int idx;
    char *tok;
    int last = 0;
    int r;

    r = func_0011C8B0(unit, &cur, (gSceMc2SysInfo + unit)->root, 0);
    if (r != 0)
        return r;
    if (func_001290C4(cur.name) >= 0x20 || func_00128E6C(cur.name, D_00138CF0) != 0)
        return 0x81019002;
    if (func_00128E6C(path, D_00138D08) == 0) {
        *entry = cur;
        return 0x81010011;
    }
    tok = func_0011BE48(path, D_00138D08);
    while (1) {
        func_00128FB0(name, tok);
        tok = func_0011BE48(0, D_00138D08);
        if (tok == 0)
            last = 1;
        parent = cur;
        r = func_0011D9E8(unit, &cur, &idx, name, parent.cluster, parent.length);
        if (cur.mode & 0x2000)
            goto bad;
        if (last == 1)
            break;
        else if (r != 0) {
            if (r == (int)0x81010002)
                return 0x81019FFF;
            return r;
        }
    }
    if (r == 0) {
        if (entry != 0)
            *entry = cur;
        if (dir_entry != 0)
            *dir_entry = idx;
        if (cluster != 0)
            *cluster = parent.cluster;
        return 0x81010011;
    }
    if (r != (int)0x81010002)
        return r;
    if (entry != 0)
        *entry = parent;
    if (dir_entry != 0)
        *dir_entry = 0;
    if (cluster != 0)
        *cluster = parent.cluster;
    return 0x81010002;
bad:
    return 0x8101000D;
}
