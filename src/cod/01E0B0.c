/* asm/cod/01E0B0.s -> func_0011E0B0.
 * libmc directory-entry write (pair of 01C8B0): FAT walk, read-modify-write of one 0x200 entry; the -1 end marker is an asm lui/ori pair as in 01C510 (Session 34)
 * MATCHED. */
extern char D_0015F080[];

int _sceMcpReadUserClust(int port, void *buf, int clust, int count);
int _sceMcpWriteUserClust(int port, void *buf, int clust, int count);
int func_0011C4C8(int port, int clust, int *err);

int func_0011E0B0(int port, char *src, int clust, int n) {
    int err = 0;
    int ret = 0x8101006F;
    unsigned int m1;

    __asm__ ("lui %0, 0xFFFF" : "=r" (m1));
    __asm__ ("ori %0, %0, 0xFFFF" : "+r" (m1));

    for (;;) {
        if (n < 2) {
            if (_sceMcpReadUserClust(port, D_0015F080, clust, 1) == 0) return 0x8101006F;
            __builtin_memcpy(D_0015F080 + n * 0x200, src, 0x200);
            if (_sceMcpWriteUserClust(port, D_0015F080, clust, 1) != 0) ret = 0;
            return ret;
        }
        clust = func_0011C4C8(port, clust, &err);
        if (err != 0) return err;
        if ((unsigned int)clust == m1) return 0x8101006F;
        clust &= 0x7FFFFFFF;
        n -= 2;
    }
}
