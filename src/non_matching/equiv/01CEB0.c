/* C equivalent of _sceMcFatFormat (01CEB0, 2348 B @ 0x0011CEB0).
 *
 * Reconstructed from asm/cod/01CEB0.s and the REA/Ghidra Emotion Engine
 * dossier ev_71747df916e24c22bdbd26c9c7524ad02447e76813ecfc2bed664c6bc476b696;
 * the callee prototypes come from the matched libmc2 helpers (_sceMcpMakeSpecoutBlock
 * 020DA0, the _sceMcp* RPC wrappers) and the struct layout from the image
 * offsets.  Readable reconstruction: NOT byte-exact (28 diff instructions in
 * register allocation and one constant pair), not part of the build.  The
 * codegen-tuned near-miss is src/non_matching/01CEB0.c.
 *
 * libmc FAT format:
 *   1. reset the per-port FAT cache, read the card spec and the superblock;
 *   2. if the magic does not match, rebuild the bad-block list and the
 *      superblock (magic + version, geometry, backup blocks skipping bad
 *      blocks, indirect FAT list, cluster size);
 *   3. write the empty FAT clusters and the indirect-FAT clusters;
 *   4. mark every allocatable cluster good (0x7FFFFFFF) or bad (-3), tracking
 *      the first good cluster and the allocation window;
 *   5. write the root directory's "." and ".." entries (BCD timestamps);
 *   6. flush, re-read the sysinfo and report.
 *
 * Behaviour derived from the target:
 *   1CEBC  lui/addu %lo gSceMc2SysInfo  -> one 0x184-byte record per port
 *   1CF10  mult 0x184                    -> si = &gSceMc2SysInfo[port]
 *   1CF94  addiu a2,s2,0xD0              -> _sceMcpMakeSpecoutBlock(port, spec, bb)
 *   1CFEC  lw/lw 0x1C/0x28               -> ELF-style magic, then strcat version
 *   1D044  div 0x400/spec.page           -> pages_per_cluster
 *   1D080  andi a3,0xFFFF / divu         -> unsigned halfword geometry
 *   1D164  (nfat*4-1)/0x400+1            -> indirect FAT list size
 *   1D2C0  lui s7,%hi(0x15E348)          -> writes table[0x100] then table[0]
 *   1D3C8  div1 + mult 1000              -> limit = card/1000*1000 + 1
 *   1D51C  ori 0x8427 / 0xA426           -> root entry modes
 *   1D600  BCD fields                    -> sceCdCLOCK -> sceMcStDateTime
 */
typedef struct {
    unsigned char resv2, sec, min, hour;
    unsigned char day, month;
    unsigned short year;
} sceMcStDateTime;

typedef struct {
    unsigned char stat, second, minute, hour;
    unsigned char pad, day, month, year;
} sceCdCLOCK;

struct sce_mc_dir_entry {           /* 0x200-byte directory entry */
    unsigned short mode;            /* 0x00 */
    unsigned short pad02;
    int length;                     /* 0x04 */
    sceMcStDateTime created;        /* 0x08 */
    int cluster;                    /* 0x10 */
    int dir_entry;                  /* 0x14 */
    sceMcStDateTime modified;       /* 0x18 */
    int attr;                       /* 0x20 */
    int pad24[7];
    char name[32];                  /* 0x40 */
    char pad60[0x200 - 0x60];
};

struct mc2_sys_info {               /* card superblock, 0x184 bytes per port */
    char magic[0x28];               /* 0x000: "Sony PS2 Memory Card Format 1.2.0.0" */
    unsigned short page_len;        /* 0x028 */
    unsigned short pages_per_cluster;   /* 0x02A */
    unsigned short pages_per_block; /* 0x02C */
    unsigned short f2E;             /* 0x02E */
    int clusters_per_card;          /* 0x030 */
    int alloc_offset;               /* 0x034 */
    int alloc_end;                  /* 0x038 */
    int rootdir_cluster;            /* 0x03C */
    int backup_block1;              /* 0x040 */
    int backup_block2;              /* 0x044 */
    int f48;                        /* 0x048 */
    int f4C;                        /* 0x04C */
    int ifc_list[32];               /* 0x050: indirect FAT cluster list */
    unsigned int bad_block_list[32];/* 0x0D0 */
    unsigned char card_type;        /* 0x150 */
    unsigned char card_flags;       /* 0x151 */
    unsigned short f152;
    int cluster_size;               /* 0x154 */
    int fat_per_cluster;            /* 0x158 */
    int clusters_per_block;         /* 0x15C */
    int f160;
    int f164;
    int f168;
    int f16C;
    int f170;                       /* first allocatable cluster offset */
    int f174;
    int f178;
    int f17C;
    int f180;
};

struct fat_cache {                  /* per-port FAT cache, 0x898 bytes */
    int table[0x200];               /* 0x000: 0x100 words staged for write-back */
    int f800;
    int f804;
    char path[0x80];
    int f888;
    int f88C;
    int f890;
    int f894;
};

struct card_spec { int page; int block; int size; int f0C; };

extern struct mc2_sys_info gSceMc2SysInfo[];
extern struct fat_cache D_0015DF48[];
extern char D_0015F080[];           /* 0x400-byte page buffer for the root dir */
extern char D_00138D08[];           /* "/" */
extern char D_00138D10[];           /* "Sony PS2 Memory Card Format " */
extern char D_00138D30[];           /* format version suffix */
extern char D_00138D40[];           /* "libmc2: Fatal Error [%08x]\n" */
extern char D_00138CF0[];           /* "." */
extern char D_00138CF8[];           /* ".." */

int _sceMcCoreGetConnection(int port);
int _sceMcpGetCardSpec(int port, struct card_spec *spec);
int _sceMcpReadSysInfo(int port);
int func_00129200(const char *a, const char *b, int n);   /* strncmp */
int _sceMcpMakeSpecoutBlock(int port, struct card_spec *spec,
                            unsigned int *bad_block_list);
void *func_001283D0(void *dst, int c, unsigned int n);    /* memset */
void *func_001293B8(void *dst, const void *src, unsigned int n);  /* memcpy */
char *func_00128BB0(char *dst, const char *src);          /* strcat */
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

static __inline__ int from_bcd(unsigned char x)
{
    return (x >> 4) * 10 + (x & 0xF);
}

int _sceMcFatFormat(int port)
{
    struct mc2_sys_info *si = &gSceMc2SysInfo[port];
    struct card_spec spec;
    sceCdCLOCK clk;
    int err;
    int *ifc;
    struct sce_mc_dir_entry *ent;
    int r, i, j, fp, nfat, nifc, clust, good, limit;

    if (_sceMcCoreGetConnection(port) == 0)
        return 0x81010013;

    D_0015DF48[port].f894 = 0;
    D_0015DF48[port].f800 = -1;
    D_0015DF48[port].f804 = -1;
    D_0015DF48[port].f890 = 0;
    D_0015DF48[port].path[0] = '/';
    D_0015DF48[port].path[1] = '\0';

    if (_sceMcpGetCardSpec(port, &spec) == 0)
        goto fail;
    if (_sceMcpReadSysInfo(port) == 0)
        goto fail;

    /* a blank or foreign card gets a fresh superblock */
    if (func_00129200(si->magic, D_00138D10, 0x1B) != 0) {
        for (i = 31; i >= 0; i--)
            si->bad_block_list[i] = 0xFFFFFFFF;
        if (_sceMcpMakeSpecoutBlock(port, &spec, si->bad_block_list) == 0)
            goto fail;
    }

    func_001283D0(si->magic, 0, 0x28);
    __builtin_memcpy(si->magic, D_00138D10, 0x1C);  /* magic string */
    func_00128BB0(si->magic, D_00138D30);           /* version suffix */
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

    /* the two backup blocks sit just below the last block, skipping bad ones */
    si->backup_block1 = spec.size / spec.block - 1;
    ifc = si->ifc_list;
    while (_sceMcpIsSpeckOutBlock(port, si->backup_block1) != 0)
        si->backup_block1--;
    si->backup_block2 = si->backup_block1 - 1;
    while ((r = _sceMcpIsSpeckOutBlock(port, si->backup_block2)) != 0)
        si->backup_block2--;
    _sceMcCoreSetWriteBackHole(port, si->backup_block2, si->backup_block1);

    /* geometry: first allocatable cluster and FAT/indirect-FAT sizes */
    clust = spec.block * spec.page / 0x400;
    nfat = (si->clusters_per_card * 4 - 1) / 0x400 + 1;
    nifc = (nfat * 4 - 1) / 0x400 + 1;
    if (nifc > 32) {
        nifc = 32;
        nfat = 0x2000;
    }

    /* reserve one cluster per indirect-FAT entry */
    func_001283D0(ifc, 0, 0x80);
    for (i = r; i < nifc; i++) {
        do {
            r = _sceMcpIsSpeckOutClust(port, clust);
            if (r == 1)
                clust++;
        } while (r != 0);
        ifc[i] = clust;
        clust++;
    }

    /* write the empty FAT clusters in 0x100-entry pages */
    fp = 0;
    j = 0;
    for (i = 255; i >= 0; i--)
        D_0015DF48[port].table[i] = -1;
    for (i = 255; i >= 0; i--)
        D_0015DF48[port].table[0x100 + i] = -1;
    for (i = nfat - 1; i >= 0; i--) {
        while (_sceMcpIsSpeckOutClust(port, clust) != 0)
            clust++;
        if (_sceMcpWriteClust(port, &D_0015DF48[port].table[0x100], clust, 1) == 0)
            goto fail;
        D_0015DF48[port].table[j++] = clust;
        if (j >= 0x100 || i == 0) {
            if (_sceMcpWriteClust(port, D_0015DF48[port].table, ifc[fp++], 1) == 0)
                goto fail;
            for (j = 255; j >= 0; j--)
                D_0015DF48[port].table[j] = -1;
            j = 0;
        }
        clust++;
    }

    /* mark the allocatable clusters, remembering the first good one */
    si->alloc_offset = clust;
    good = 0;
    si->alloc_end = si->backup_block2 * si->pages_per_block /
                        si->pages_per_cluster - clust;
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
    si->alloc_end = si->backup_block2 * si->pages_per_block /
                        si->pages_per_cluster - si->alloc_offset;

    r = func_0011C6A8(port, &err);
    if (err != 0)
        return err;
    if (r != 0) {
        scePrintf(D_00138D40, r);
        return 0x81019001;
    }

    /* root directory: "." and ".." */
    _sceMcCoreReadClock(port, &clk);
    ent = (struct sce_mc_dir_entry *)D_0015F080;
    func_001283D0(ent, 0, 0x200);
    ent->mode = 0x8427;
    ent->length = 2;
    ent->created.year = from_bcd(clk.year) + 2000;
    ent->created.month = from_bcd(clk.month);
    ent->created.day = from_bcd(clk.day);
    ent->created.hour = from_bcd(clk.hour);
    ent->created.min = from_bcd(clk.minute);
    ent->created.sec = from_bcd(clk.second);
    ent->pad02 = 0;
    ent->created.resv2 = 0;
    ent->cluster = 0;
    ent->dir_entry = 0;
    ent->modified = ent->created;
    ent->attr = 0;
    ent->name[0] = '.';
    ent->name[1] = '\0';

    ent++;
    func_001283D0(ent, 0, 0x200);
    ent->mode = 0xA426;
    ent->length = 0;
    ent->created.year = from_bcd(clk.year) + 2000;
    ent->created.month = from_bcd(clk.month);
    ent->created.day = from_bcd(clk.day);
    ent->created.hour = from_bcd(clk.hour);
    ent->created.min = from_bcd(clk.minute);
    ent->created.sec = from_bcd(clk.second);
    ent->pad02 = 0;
    ent->created.resv2 = 0;
    ent->cluster = 0;
    ent->dir_entry = 0;
    ent->modified = ent->created;
    ent->attr = 0;
    ent->name[0] = '.';
    ent->name[1] = '.';
    ent->name[2] = '\0';

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
