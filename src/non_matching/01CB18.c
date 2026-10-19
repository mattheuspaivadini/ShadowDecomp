/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 23 [cc=29].
 * _sceMcFatGetInfo. ver and the free-entry count share one variable; version check fails when ver <
 * 11. Residual = v0/v1 pseudo order in the D_0015DF48 index after ClearNewCardFlag and in the
 * /1000*1000 limit, plus the final err test.
 * Tried: five ver expressions, block-scoped count, if/else on err, store reorders, r reused for both
 * (105).
 * The original .s stays in the build (asm/cod/01CB18.s); this C
 * draft (Session 34) is kept for the record. */
struct F { char pad00[0x800]; int f800; int f804; char path[0x80]; int f888; int f88C; int f890; int f894; };
struct Mc2SysInfo {
    char magic[0x1C];           /* 0x00 */
    char ver[4];                /* 0x1C "x.y" */
    char pad20[0x10];
    int f30;                    /* 0x30 */
    int f34;                    /* 0x34 */
    int f38;                    /* 0x38 */
    int f3C;                    /* 0x3C */
    int f40;                    /* 0x40 */
    int f44;                    /* 0x44 */
    char pad48[0x170 - 0x48];
    int f170;                   /* 0x170 */
    char pad174[0x184 - 0x174];
};
struct Spec { int w0; int w4; int w8; int wC; };
struct DirEnt { unsigned short attr; char pad02[0x3E]; char name[0x20]; char pad60[0x1A0]; };

extern struct F D_0015DF48[];
extern struct Mc2SysInfo gSceMc2SysInfo[];
extern char D_00138D08[];   /* "/" */
extern char D_00138D10[];
extern char D_00138CF0[];   /* "." */
extern char D_00138CF8[];   /* ".." */

int _sceMcCoreGetConnection(int port);
int _sceMcpCheckNewCard(int port);
void _sceMcCoreClearNewCardFlag(int port);
int _sceMcpGetCardSpec(int port, struct Spec *spec);
int _sceMcpReadSysInfo(int port);
int func_00129200(const char *a, const char *b, int ver);   /* strncmp */
int func_00128E6C(const char *a, const char *b);          /* strcmp */
void func_0011CAC0(int port, struct Mc2SysInfo *sys);
void _sceMcCoreSetWriteBackHole(int port, int a, int b);
void _sceMcCoreWriteBack(int port);
int _sceMcpIsSpeckOutClust(int port, int clust);
int func_0011C8B0(int port, struct DirEnt *ent, int clust, int ver);
int func_0011C7D8(int port, int *err);

int _sceMcFatGetInfo(int port, int *info) {
    struct Spec spec;
    struct DirEnt ent;
    int err;
    struct Mc2SysInfo *sys = &gSceMc2SysInfo[port];
    int r;
    int ver;
    int cnt;
    int i;
    int c;
    int lim;

    if (_sceMcCoreGetConnection(port) == 0)
        return 0x81010013;
    if (info != 0) {
        info[1] = 0;
        info[0] = 0;
        info[2] = 0;
    }
    r = _sceMcpCheckNewCard(port);
    if (r == 0)
        return 0x81010013;
    if (r == 2) {
        _sceMcCoreClearNewCardFlag(port);
        D_0015DF48[port].f888 = 1;
    }
    if (D_0015DF48[port].f888 != 0) {
        if (_sceMcpGetCardSpec(port, &spec) == 0 || spec.w0 == 0)
            return 0x8101006F;
        D_0015DF48[port].f894 = 0;
        D_0015DF48[port].f800 = -1;
        D_0015DF48[port].f804 = -1;
        D_0015DF48[port].f890 = 0;
        __builtin_memcpy(D_0015DF48[port].path, D_00138D08, 2);
        if (_sceMcpReadSysInfo(port) == 0)
            return 0x8101006F;
        if (info != 0)
            info[0] = 2;
        if (func_00129200(sys->magic, D_00138D10, 0x1B) != 0) {
            if (info != 0)
                info[1] = 0;
            return 0x8101002F;
        }
        ver = (sys->ver[0] - '0') * 10;
        ver = ver - '0' + sys->ver[2];
        if (ver < 11)
            return 0x81010086;
        func_0011CAC0(port, sys);
        cnt = 0;
        _sceMcCoreSetWriteBackHole(port, sys->f44, sys->f40);
        i = 0;
        _sceMcCoreWriteBack(port);
        lim = sys->f30 / 1000 * 1000 + 1;
        c = sys->f34;
        for (; i < sys->f38; i++, c++) {
            if (cnt == lim)
                sys->f170 = c - sys->f34;
            if (_sceMcpIsSpeckOutClust(port, c) == 0)
                cnt++;
        }
        err = func_0011C8B0(port, &ent, sys->f3C, 0);
        if (err != 0)
            return err;
        if (!(ent.attr & 0x8000) || func_00128E6C(ent.name, D_00138CF0) != 0)
            return 0x8101002F;
        err = func_0011C8B0(port, &ent, sys->f3C, 1);
        if (err != 0)
            return err;
        if (!(ent.attr & 0x8000) || func_00128E6C(ent.name, D_00138CF8) != 0)
            return 0x8101002F;
        D_0015DF48[port].f88C = 1;
    }
    if (D_0015DF48[port].f88C == 0)
        return 0x8101002F;
    if (info != 0) {
        ver = func_0011C7D8(port, &err);
        if (err != 0)
            return err;
        info[0] = 2;
        info[1] = D_0015DF48[port].f88C;
        info[2] = ver;
    }
    if (D_0015DF48[port].f888 != 0) {
        D_0015DF48[port].f888 = 0;
        return 0x81019003;
    }
    return 0;
}
