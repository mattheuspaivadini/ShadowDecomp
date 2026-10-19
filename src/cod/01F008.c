/* asm/cod/01F008.s -> _sceMcFatReadFile.
 * _sceMcFatReadFile; clust read before total = size (fixes the size/total register roles), asm lui/ori end marker (Session 35)
 * MATCHED. */
struct McDirEnt {
    unsigned short attr;        /* 0x00 */
    unsigned short pad02;
    int size;                   /* 0x04 */
    char pad08[8];
    int clust;                  /* 0x10 */
    char pad14[0x200 - 0x14];
};

extern char D_0015F080[];

int func_0011D8E0(int port);
int func_0011D988(int port, const char *name, char *path);
int func_0011DC60(int port, char *path, struct McDirEnt *ent, int a3, int a4);
int _sceMcpReadUserClust(int port, void *buf, int clust, int count);
int func_0011C4C8(int port, int clust, int *err);
void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */

int _sceMcFatReadFile(int port, const char *name, char *buf, int pos, int size) {
    struct McDirEnt ent;
    char path[0x80];
    int err;
    int r;
    int total;
    int clust;
    int n;
    unsigned int m1;

    if ((r = func_0011D8E0(port)) != 0) return r;
    if ((r = func_0011D988(port, name, path)) != 0) return r;
    r = func_0011DC60(port, path, &ent, 0, 0);
    if (r != 0x81010011) return r;
    if (!(ent.attr & 1)) return 0x8101000D;
    if (ent.attr & 0x2000) return 0x8101000D;
    if (ent.attr & 0x20) return 0x81010002;
    if (ent.size < pos) return 0x81010016;
    if (size == 0) size = ent.size - pos;
    if (ent.size < size + pos) size = ent.size - pos;
    clust = ent.clust;
    total = size;
    if (total != 0) {
        __asm__ ("lui %0, 0xFFFF" : "=r" (m1));
        __asm__ ("ori %0, %0, 0xFFFF" : "+r" (m1));
        do {
            if (pos < 0x400) {
                err = _sceMcpReadUserClust(port, D_0015F080, clust, 1);
                if (err == 0) return 0x8101006F;
                n = 0x400 - pos;
                if (!(n < size)) {
                    func_0012821C(buf, D_0015F080 + pos, size);
                    return total;
                }
                func_0012821C(buf, D_0015F080 + pos, n);
                buf += 0x400 - pos;
                    size -= 0x400 - pos;
                pos = 0;
            }
            clust = func_0011C4C8(port, clust, &err);
            if (err != 0) return err;
            if ((unsigned int)clust == m1) return 0x81019002;
            clust &= 0x7FFFFFFF;
            if (pos != 0) pos -= 0x400;
        } while (size != 0);
    }
    return total;
}
