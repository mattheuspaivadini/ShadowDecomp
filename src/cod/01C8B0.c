/* asm/cod/01C8B0.s -> func_0011C8B0.
 * libmc directory-entry read: walk the FAT chain two entries per cluster, then a builtin 0x200 copy out of D_0015F080 (Session 34)
 * MATCHED. */
extern char D_0015F080[];

int _sceMcpReadUserClust(int port, void *buf, int clust, int count);
int func_0011C510(int port, int clust, int *err);

int func_0011C8B0(int port, char *dst, int clust, int n) {
    int err = 0;

    for (;;) {
        if (n < 2) {
            if (_sceMcpReadUserClust(port, D_0015F080, clust, 1) == 0) return 0x8101006F;
            __builtin_memcpy(dst, D_0015F080 + n * 0x200, 0x200);
            dst[0x5F] = '\0';
            return 0;
        }
        clust = func_0011C510(port, clust, &err);
        if (err == 0x81010059) return 0x81010002;
        if (err != 0) return err;
        n -= 2;
    }
}
