/* asm/cod/020370.s -> _sceMcFatGetEntSpace.
 * Memory-card FAT entry-space query: card check, path resolve, directory lookup (0x81010011 = found), then func_0011E258 with an address-taken err (Session 28).
 * MATCHED. */
struct SceMcDirEntry {
    unsigned short mode;        /* 0x00 */
    unsigned short pad02;
    int f04;                    /* 0x04 */
    int pad08[2];
    int f10;                    /* 0x10 */
    char pad14[0x200 - 0x14];
};

int func_0011D8E0(int unit);
int func_0011D988(int unit, const char *dir, char *path);
int func_0011DC60(int unit, const char *path, struct SceMcDirEntry *entry, int a3, int a4);
int func_0011E258(int unit, int a1, int a2, int *err);

int _sceMcFatGetEntSpace(int unit, const char *dir) {
    struct SceMcDirEntry entry;
    char path[0x80];
    int err;
    int ret;

    err = func_0011D8E0(unit);
    if (err != 0)
        return err;
    err = func_0011D988(unit, dir, path);
    if (err != 0)
        return err;
    err = func_0011DC60(unit, path, &entry, 0, 0);
    if (err != (int)0x81010011)
        return err;
    if ((entry.mode & 0x20) == 0)
        return (int)0x81010014;
    ret = func_0011E258(unit, entry.f10, entry.f04, &err);
    if (err != 0)
        return err;
    return ret;
}
