/* C equivalent of func_0011D9E8 (01D9E8, 628 B @ 0x0011D9E8).
 *
 * Reconstructed from asm/cod/01D9E8.s and the REA/Ghidra Emotion Engine
 * dossier ev_fa31cdad880e076ec0f9da6616d624e14bce4f71d80c533f5874e878c0cb2d83;
 * the cluster/entry layout follows the matched libmc2 helpers.  Readable
 * reconstruction: NOT byte-exact (20 diff instructions in the block layout),
 * not part of the build.  The codegen-tuned near-miss is
 * src/non_matching/archive/01D9E8.c.
 *
 * Case-insensitive search of a FAT directory cluster chain for `name`.
 * The first cluster of a directory holds "." and ".." and must be validated;
 * entries with the 0x8000 attribute bit are live, and the 31st character of
 * the 32-byte name is forced to NUL before the comparison.
 *
 * Behaviour derived from the target:
 *   1D9F8  daddu fp,a3            -> name is the 4th argument
 *   1DA34  first = 1, n = 0       -> entry ordinal returned through *idx
 *   1DB5C  s6 = a2                -> idx
 *   1DB74  subu s2,slt(0,s2)      -> count -= (count > 0)
 *   1DBB4  lui/ori 0xFFFFFFFF     -> (unsigned)clust == 0xFFFFFFFF ends the chain
 *   1DBC4  and 0x7FFFFFFF         -> clust mask before the next read
 *   1DC00  sb zero / strlen       -> first-cluster validation of "./.."
 *   1DC18  0x81019002             -> "not a directory" error block
 *   1DC24  0x81010002             -> end of chain without a match
 */
struct dir_ent {                    /* one 0x200-byte memory-card entry */
    unsigned short attr;            /* 0x00: 0x8000 = entry in use */
    char pad02[0x3E];
    char name[0x20];                /* 0x40 */
    char pad60[0x1A0];
};

extern char D_00138CF0[];           /* "." */
extern char D_00138CF8[];           /* ".." */

int _sceMcpReadUserClust(int port, void *buf, int clust, int count);
int func_0011C4C8(int port, int clust, int *err);   /* next cluster of a chain */
unsigned int func_001290C4(const char *s);          /* strlen */
int func_00128E6C(const char *a, const char *b);    /* strcmp */

int func_0011D9E8(int port, struct dir_ent *out, int *idx, const char *name,
                  int clust, int count)
{
    struct dir_ent buf[2];
    int err = 0;
    int first = 1;
    int n = 0;
    struct dir_ent *ent;
    int i;

    for (;;) {
        if (_sceMcpReadUserClust(port, buf, clust, 1) == 0)
            return 0x8101006F;

        if (first) {
            first = 0;
            if (func_001290C4(buf[0].name) >= 0x20)
                break;
            if (func_00128E6C(buf[0].name, D_00138CF0) != 0 ||
                func_001290C4(buf[1].name) >= 0x20 ||
                func_00128E6C(buf[1].name, D_00138CF8) != 0)
                return 0x81019002;
        }

        ent = buf;
        for (i = 0; i < 2 && count != 0; i++) {
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
            count -= count > 0;
            ent++;
            n++;
        }

        clust = func_0011C4C8(port, clust, &err);
        if (err != 0)
            return err;
        if ((unsigned int)clust == 0xFFFFFFFF)
            return 0x81010002;
        clust &= 0x7FFFFFFF;
    }
    return 0x81019002;
}
