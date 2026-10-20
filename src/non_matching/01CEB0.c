/* STATUS (Session 36, 2026-10-20): NON_MATCHING. best score 315 [cc=29].
 * libmc FAT format: reset the per-port FAT cache, read the card spec and superblock, rebuild the
 * superblock (magic + version, geometry, backup blocks skipping bad blocks, indirect FAT list),
 * write the empty FAT and indirect clusters, mark good/bad allocatable clusters, write the root
 * dot/dotdot entries, flush and re-read. Levers that worked: unsigned 0xFFFFFFFF bad-block fill,
 * 4-aligned magic source and field for the 28-byte lw tail, an extra 16-byte local (frame 0xE0),
 * alloc_end before the /1000 limit (div/div1 pairing), the fail label inside the last check.
 * Residual: si allocated to s3 instead of s2 (register asm pin makes gcc copy it), the ifc_list
 * pointer is hoisted by sched1 to the block start (original stores it in the jump slot into the
 * backup-block loop), a dead a2 = &bad_block_list in the original, the nifc/first-cluster
 * arithmetic order, and the nfat loop entry (bltzl).
 * The original .s stays in the build (asm/cod/01CEB0.s); this C
 * draft (Session 36) is kept for the record. */
typedef struct {
    unsigned char resv2, sec, min, hour;
    unsigned char day, month;
    unsigned short year;
} sceMcStDateTime;

typedef struct {
    unsigned char stat, second, minute, hour;
    unsigned char pad, day, month, year;
} sceCdCLOCK;

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

struct Mc2SysInfo {             /* the card superblock, 0x184 bytes per port */
    char magic[0x28] __attribute__((aligned(4))); /* 0x000 */
    unsigned short page_len;    /* 0x028 */
    unsigned short pages_per_cluster; /* 0x02A */
    unsigned short pages_per_block; /* 0x02C */
    unsigned short f2E;         /* 0x02E */
    int clusters_per_card;      /* 0x030 */
    int alloc_offset;           /* 0x034 */
    int alloc_end;              /* 0x038 */
    int rootdir_cluster;        /* 0x03C */
    int backup_block1;          /* 0x040 */
    int backup_block2;          /* 0x044 */
    int f48;                    /* 0x048 */
    int f4C;                    /* 0x04C */
    int ifc_list[32];           /* 0x050 */
    unsigned int bad_block_list[32]; /* 0x0D0 */
    unsigned char card_type;    /* 0x150 */
    unsigned char card_flags;   /* 0x151 */
    unsigned short f152;
    int cluster_size;           /* 0x154 */
    int fat_per_cluster;        /* 0x158 */
    int clusters_per_block;     /* 0x15C */
    int f160;
    int f164;                   /* 0x164 */
    int f168;                   /* 0x168 */
    int f16C;                   /* 0x16C */
    int f170;                   /* 0x170 */
    int f174;                   /* 0x174 */
    int f178;                   /* 0x178 */
    int f17C;                   /* 0x17C */
    int f180;                   /* 0x180 */
};

struct F {                      /* per-port FAT cache, 0x898 bytes */
    int table[0x200];
    int f800;
    int f804;
    char path[0x80];
    int f888;
    int f88C;
    int f890;
    int f894;
};

struct CardSpec { int page; int block; int size; int f0C; };

extern struct Mc2SysInfo gSceMc2SysInfo[];
extern struct F D_0015DF48[];
extern char D_0015F080[];
extern char D_00138D08[];       /* "/" */
extern char D_00138D10[] __attribute__((aligned(4)));  /* "Sony PS2 Memory Card Format " */
extern char D_00138D30[];       /* format version */
extern char D_00138D40[];       /* scePrintf format */
extern char D_00138CF0[];       /* "." */
extern char D_00138CF8[];       /* ".." */

int _sceMcCoreGetConnection(int port);
int _sceMcpGetCardSpec(int port, struct CardSpec *spec);
int _sceMcpReadSysInfo(int port);
int func_00129200(const char *a, const char *b, int n);   /* strncmp */
int _sceMcpMakeSpecoutBlock(int port, struct CardSpec *spec);
void *func_001283D0(void *dst, int c, int n);               /* memset */
char *func_00128BB0(char *dst, const char *src);           /* strcat */
int _sceMcpIsSpeckOutBlock(int port, int block);
int _sceMcCoreSetWriteBackHole(int port, int a, int b);
int _sceMcpIsSpeckOutClust(int port, int clust);
int _sceMcpWriteClust(int port, void *buf, int clust, int n);
int func_0011C578(int port, int clust, int value, int *err);
int func_0011C6A8(int port, int *err);
void scePrintf(const char *fmt, ...);
int _sceMcCoreReadClock(int port, sceCdCLOCK *clk);
int _sceMcpWriteUserClust(int port, void *buf, int clust, int n);
int _sceMcpFlushCache(int port);
int func_0011C320(int port);
int _sceMcpWriteSysInfo(int port);
int _sceMcFatGetInfo(int port, int a1);

static __inline__ int BCD(unsigned char x) { return (x >> 4) * 10 + (x & 0xF); }

int _sceMcFatFormat(int port) {
    struct Mc2SysInfo *si = &gSceMc2SysInfo[port];
    struct CardSpec spec;
    sceCdCLOCK clk;
    int pad[4];
    int err;
    int *ifc;
    struct SceMcDirEntry *ent;
    int r;
    int i;
    int j;
    int k;
    int fp;
    int nfat;
    int nifc;
    int clust;
    int good;
    int limit;

    if (_sceMcCoreGetConnection(port) == 0)
        return 0x81010013;
    D_0015DF48[port].f894 = 0;
    D_0015DF48[port].f800 = -1;
    D_0015DF48[port].f804 = -1;
    D_0015DF48[port].f890 = 0;
    __builtin_memcpy(D_0015DF48[port].path, D_00138D08, 2);
    if (_sceMcpGetCardSpec(port, &spec) == 0)
        goto fail;
    if (_sceMcpReadSysInfo(port) == 0)
        goto fail;
    if (func_00129200(si->magic, D_00138D10, 0x1B) != 0) {
        for (i = 31; i >= 0; i--)
            si->bad_block_list[i] = 0xFFFFFFFF;
        if (_sceMcpMakeSpecoutBlock(port, &spec) == 0)
            goto fail;
    }
    func_001283D0(si->magic, 0, 0x28);
    __builtin_memcpy(si->magic, D_00138D10, 0x1C);
    func_00128BB0(si->magic, D_00138D30);
    si->page_len = spec.page;
    si->pages_per_cluster = 0x400 / spec.page;
    si->pages_per_block = spec.block;
    si->f2E = 0xFF00;
    si->clusters_per_card = spec.size / si->pages_per_cluster;
    si->cluster_size = 0x400;
    si->card_type = 2;
    si->card_flags = 0x2B;
    si->fat_per_cluster = 0x100;
    si->rootdir_cluster = 0;
    si->f48 = 0;
    si->f4C = 0;
    si->f170 = 0;
    si->clusters_per_block = si->pages_per_block / si->pages_per_cluster;
    si->f180 = -1;
    si->f164 = 0;
    si->f168 = 0;
    si->f16C = 0;
    si->f174 = -1;
    si->f178 = -1;
    si->f17C = -1;
    si->backup_block1 = spec.size / spec.block - 1;
    while (_sceMcpIsSpeckOutBlock(port, si->backup_block1) != 0)
        si->backup_block1--;
    si->backup_block2 = si->backup_block1 - 1;
    while ((r = _sceMcpIsSpeckOutBlock(port, si->backup_block2)) != 0)
        si->backup_block2--;
    _sceMcCoreSetWriteBackHole(port, si->backup_block2, si->backup_block1);
    nfat = (si->clusters_per_card * 4 - 1) / 0x400 + 1;
    nifc = (nfat * 4 - 1) / 0x400 + 1;
    clust = (spec.block * spec.page + 0x3FF) / 0x400;
    if (nifc > 32) {
        nifc = 32;
        nfat = 0x2000;
    }
    ifc = si->ifc_list;
    func_001283D0(ifc, 0, 0x80);
    for (i = r; i < nifc; i++) {
        while ((r = _sceMcpIsSpeckOutClust(port, clust)) != 0) {
            if (r == 1)
                clust++;
        }
        ifc[i] = clust;
        clust++;
    }
    for (i = 255; i >= 0; i--)
        D_0015DF48[port].table[i] = -1;
    for (i = 255; i >= 0; i--)
        D_0015DF48[port].table[0x100 + i] = -1;
    j = 0;
    fp = 0;
    for (k = nfat - 1; k >= 0; k--) {
        while (_sceMcpIsSpeckOutClust(port, clust) != 0)
            clust++;
        if (_sceMcpWriteClust(port, &D_0015DF48[port].table[0x100], clust, 1) == 0)
            goto fail;
        D_0015DF48[port].table[j++] = clust;
        if (j >= 0x100 || k == 0) {
            if (_sceMcpWriteClust(port, D_0015DF48[port].table, ifc[fp++], 1) == 0)
                goto fail;
            for (i = 255; i >= 0; i--)
                D_0015DF48[port].table[i] = -1;
            j = 0;
        }
        clust++;
    }
    si->alloc_offset = clust;
    good = 0;
    si->alloc_end = si->backup_block2 * si->pages_per_block / si->pages_per_cluster - clust;
    limit = si->clusters_per_card / 1000 * 1000 + 1;
    for (i = 0; i < si->alloc_end; i++, clust++) {
        if (good == limit)
            si->f170 = clust - si->alloc_offset;
        if (_sceMcpIsSpeckOutClust(port, clust) == 1) {
            func_0011C578(port, i, -3, &err);
            if (err != 0)
                return err;
        } else {
            if (good == 0)
                si->alloc_offset = clust;
            func_0011C578(port, i, 0x7FFFFFFF, &err);
            if (err != 0)
                return err;
            good++;
        }
    }
    if (good < limit)
        return 0x81019001;
    si->alloc_end = si->backup_block2 * si->pages_per_block / si->pages_per_cluster - si->alloc_offset;
    r = func_0011C6A8(port, &err);
    if (err != 0)
        return err;
    if (r != 0) {
        scePrintf(D_00138D40, r);
        return 0x81019001;
    }
    _sceMcCoreReadClock(port, &clk);
    ent = (struct SceMcDirEntry *)D_0015F080;
    func_001283D0(ent, 0, 0x200);
    ent->mode = 0x8427;
    ent->length = 2;
    ent->created.year = BCD(clk.year) + 2000;
    ent->created.month = BCD(clk.month);
    ent->created.day = BCD(clk.day);
    ent->created.hour = BCD(clk.hour);
    ent->created.min = BCD(clk.minute);
    ent->created.sec = BCD(clk.second);
    ent->pad02 = 0;
    ent->created.resv2 = 0;
    ent->cluster = 0;
    ent->dir_entry = 0;
    ent->modified = ent->created;
    ent->attr = 0;
    __builtin_memcpy(ent->name, D_00138CF0, 2);
    ent++;
    func_001283D0(ent, 0, 0x200);
    ent->mode = 0xA426;
    ent->length = 0;
    ent->created.year = BCD(clk.year) + 2000;
    ent->created.month = BCD(clk.month);
    ent->created.day = BCD(clk.day);
    ent->created.hour = BCD(clk.hour);
    ent->created.min = BCD(clk.minute);
    ent->created.sec = BCD(clk.second);
    ent->pad02 = 0;
    ent->created.resv2 = 0;
    ent->cluster = 0;
    ent->dir_entry = 0;
    ent->modified = ent->created;
    ent->attr = 0;
    __builtin_memcpy(ent->name, D_00138CF8, 3);
    if (_sceMcpWriteUserClust(port, D_0015F080, 0, 1) == 0)
        goto fail;
    func_0011C578(port, 0, -1, &err);
    if (err != 0)
        return err;
    if (_sceMcpFlushCache(port) == 0)
        goto fail;
    if (func_0011C320(port) == 0)
        goto fail;
    if (_sceMcpWriteSysInfo(port) == 0) {
    fail:
        return 0x8101006F;
    }
    D_0015DF48[port].f888 = 1;
    if ((err = _sceMcFatGetInfo(port, 0)) == (int)0x81019003)
        err = 0;
    return err;
}
