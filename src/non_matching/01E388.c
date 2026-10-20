/* STATUS (Session 36, 2026-10-20): NON_MATCHING. best score 12 [cc=29].
 * libmc FAT: add a directory entry (walk the dir clusters two entries at a time, remember the dot
 * entry, write new_ent into the first free slot or after index used slots, extend the chain with a
 * fresh cluster, then bump the parent length). Levers that worked: empty asm +r on the buffer walk
 * pointer (the original reloads ent->mode after the dot block copy, i.e. the walk pointer is not
 * known to point at D_0015F080), update block inside the new-cluster branch reached by goto, ent++
 * then ent->mode = 0, dc local for the dot cluster. Residual = block placement after cross-jump:
 * the original keeps the 0x8101006F error block at the very end (alloc-path write failure branches
 * to it) and does not share the sw of the 0x81010017 and bad blocks. Tried: fail labels (lose the
 * s7 hoist of 0x8101006F), while (read) loop, return-shape variants.
 * The original .s stays in the build (asm/cod/01E388.s); this C
 * draft (Session 36) is kept for the record. */
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

extern char D_0015F080[];
extern char D_00138CF0[];       /* "." */

int _sceMcpReadUserClust(int unit, void *buf, unsigned int clust, int count);
int _sceMcpWriteUserClust(int unit, void *buf, unsigned int clust, int count);
int func_00128E6C(const char *a, const char *b);   /* strcmp */
unsigned int func_0011C4C8(int unit, unsigned int clust, int *err);
unsigned int func_0011C6A8(int unit, int *err);
int func_0011C578(int unit, unsigned int clust, int value, int *err);
int func_0011C8B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);
int func_0011E0B0(int unit, struct SceMcDirEntry *entry, int cluster, int dir_entry);

int func_0011E388(int unit, struct SceMcDirEntry *new_ent, unsigned int clust, int index, int *err) {
    struct SceMcDirEntry parent;
    struct SceMcDirEntry dot;
    int dc;
    int count;
    int is_root;
    struct SceMcDirEntry *ent;
    int i;
    unsigned int prev;

    dot.cluster = -1;
    is_root = clust == 0;
    count = 0;
    while (1) {
        if (_sceMcpReadUserClust(unit, D_0015F080, clust, 1) == 0) {
            *err = 0x8101006F;
            return -1;
        }
        ent = (struct SceMcDirEntry *)D_0015F080;
        __asm__ ("" : "+r" (ent));
        for (i = 0; i < 2; i++) {
            if ((ent->mode & 0x8000) && func_00128E6C(ent->name, D_00138CF0) == 0)
                dot = *ent;
            if (!(ent->mode & 0x8000) || index == 0) {
                *ent = *new_ent;
                if (_sceMcpWriteUserClust(unit, D_0015F080, clust, 1) == 0) {
                    *err = 0x8101006F;
                    return -1;
                }
                if (index != 0) {
                    *err = 0;
                    return count;
                }
                if ((dc = dot.cluster) == -1)
                    goto bad;
                goto update;
            }
            if (index > 0)
                index--;
            count++;
            ent++;
        }
        if (!is_root && count >= 20) {
            *err = 0x81010017;
            return -1;
        }
        prev = clust;
        clust = func_0011C4C8(unit, prev, err);
        if (*err != 0)
            return -1;
        if (clust == 0xFFFFFFFF) {
            clust = func_0011C6A8(unit, err);
            if (*err != 0)
                return -1;
            func_0011C578(unit, prev, clust | 0x80000000, err);
            if (*err != 0)
                return -1;
            func_0011C578(unit, clust, -1, err);
            if (*err != 0)
                return -1;
            ent = (struct SceMcDirEntry *)D_0015F080;
            *ent = *new_ent;
            ent++;
            ent->mode = 0;
            if (_sceMcpWriteUserClust(unit, D_0015F080, clust, 1) == 0) {
                *err = 0x8101006F;
                return -1;
            }
            if ((dc = dot.cluster) == -1)
                return 0x81019002;
        update:
            if ((*err = func_0011C8B0(unit, &parent, dc, dot.dir_entry)) != 0)
                return -1;
            parent.length++;
            if ((*err = func_0011E0B0(unit, &parent, dot.cluster, dot.dir_entry)) != 0)
                return -1;
            *err = 0;
            return count;
        }
        clust &= 0x7FFFFFFF;
    }
bad:
    *err = 0x81019002;
    return -1;
}
