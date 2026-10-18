/* asm/cod/01E258.s -> func_0011E258.
 * FAT free-entry counter over a two-page cluster buffer; page pointer walk, the last-page adjustment written as an if (Session 23)
 * MATCHED. */
struct Page { unsigned short w; char pad[0x1FE]; };
extern struct Page D_0015F080[2];
int _sceMcpReadUserClust(int port, void *buf, unsigned int clust, int n);
unsigned int func_0011C4C8(int port, unsigned int clust, int *err);

int func_0011E258(int port, unsigned int clust, int n, int *err) {
    int found = 0;
    int j;
    struct Page *buf = D_0015F080;
    struct Page *p;
    *err = 0;
    while (1) {
        if (_sceMcpReadUserClust(port, buf, clust, 1) == 0) {
            *err = 0x8101006F;
            return -1;
        }
        for (j = 0, p = buf; j < 2; j++, p++) {
            if (!(p->w & 0x8000))
                found++;
            if (--n == 0)
                {
                if (j == 0)
                    found++;
                return found;
            }
        }
        clust = func_0011C4C8(port, clust, err);
        if (*err)
            return -1;
        if (clust == 0xFFFFFFFF)
            return found;
        clust &= 0x7FFFFFFF;
    }
}
