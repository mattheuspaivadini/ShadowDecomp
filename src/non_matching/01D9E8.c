/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 123 [cc=29].
 * FAT directory search by name (first cluster checks . and ..). Prologue/frame match with while (read)
 * and a plain -1 compare. Residual = block layout: the original starts the first-cluster strlen right
 * after the read at the loop bottom and branches back into the . compare.
 * Tried: for (;;) with read first, asm lui/ori -1, goto-entered loop (133).
 * The original .s stays in the build (asm/cod/01D9E8.s); this C
 * draft (Session 34) is kept for the record. */
struct DirEnt { unsigned short attr; char pad02[0x3E]; char name[0x20]; char pad60[0x1A0]; };

extern char D_00138CF0[];   /* "." */
extern char D_00138CF8[];   /* ".." */

int _sceMcpReadUserClust(int port, void *buf, int clust, int count);
int func_0011C4C8(int port, int clust, int *err);
unsigned int func_001290C4(const char *s);                /* strlen */
int func_00128E6C(const char *a, const char *b);          /* strcmp */

int func_0011D9E8(int port, struct DirEnt *out, int *idx, const char *name, int clust, int count) {
    struct DirEnt buf[2];
    int err = 0;
    int first = 1;
    int n = 0;
    struct DirEnt *ent;
    int i;
    unsigned int m1;

    while (_sceMcpReadUserClust(port, buf, clust, 1) != 0) {
        if (first) {
            first = 0;
            if (func_001290C4(buf[0].name) >= 0x20 || func_00128E6C(buf[0].name, D_00138CF0) != 0
                || func_001290C4(buf[1].name) >= 0x20 || func_00128E6C(buf[1].name, D_00138CF8) != 0)
                return 0x81019002;
        }
        ent = buf;
        if (count != 0) {
            i = 0;
            do {
                if (ent->attr & 0x8000) {
                    ent->name[0x1F] = '\0';
                    if (func_00128E6C(name, ent->name) == 0) {
                        if (out != 0)
                            *out = *ent;
                        if (idx != 0)
                            *idx = n;
                        return 0;
                    }
                }
                i++;
                count -= count > 0;
                ent++;
                n++;
            } while (i < 2 && count != 0);
        }
        clust = func_0011C4C8(port, clust, &err);
        if (err != 0)
            return err;
        if (clust == -1)
            return 0x81010002;
        clust &= 0x7FFFFFFF;
    }
    return 0x8101006F;
}
