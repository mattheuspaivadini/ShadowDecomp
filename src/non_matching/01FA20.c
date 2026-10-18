/* STATUS (Session 28, 2026-10-18): NON_MATCHING. best score 12 [cc=29].
 * Only the s1/s2 roles differ (original: path -> s1, unit -> s2). Declaration order, a char *p alias of path and an inverted strcmp branch do not change the global-alloc order.
 * The original .s stays in the build (asm/cod/01FA20.s); this C
 * draft (Session 28) is kept for the record. */
struct SceMcFatSlot {
    char cwd[0x898];
};

struct SceMcDirEntry {
    unsigned short mode;
    char pad[0x1FE];
};

extern char D_00138D08[];
extern struct SceMcFatSlot D_0015E750[];

int func_0011D988(int unit, const char *dir, char *path);
int func_0011D8E0(int unit);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int a3, int a4);
int func_00128E6C(const char *s1, const char *s2);
char *func_00128FB0(char *dst, const char *src);
char *func_00128BB0(char *dst, const char *src);

int _sceMcFatChDir(int unit, const char *dir, char *cwd) {
    struct SceMcDirEntry entry;
    char path[0x80];
    int ret;

    ret = func_0011D988(unit, dir, path);
    if (ret != 0) {
        return ret;
    }
    if (func_00128E6C(path, D_00138D08) == 0) {
        func_00128FB0(D_0015E750[unit].cwd, path);
    } else {
        ret = func_0011D8E0(unit);
        if (ret != 0) {
            return ret;
        }
        ret = func_0011DC60(unit, path, &entry, 0, 0);
        if (ret != (int)0x81010011) {
            return ret;
        }
        if ((entry.mode & 0x20) == 0) {
            return (int)0x81010014;
        }
        func_00128FB0(D_0015E750[unit].cwd, path);
        func_00128BB0(D_0015E750[unit].cwd, D_00138D08);
    }
    if (cwd != 0) {
        func_00128FB0(cwd, path);
    }
    return 0;
}
