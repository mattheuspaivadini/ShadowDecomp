/* STATUS (Session 44, 2026-10-21): NON_MATCHING. best score 56 (was 80; sw.py diff lines).
 * LoaderSysPrintf and DecodeSection declared void as defined (002CF8, 000278): fixes most register roles after those calls. Residual: the loader's open result copy (move a0,v0; move s0,a0), the rel-count loops counting in s0 vs s3, and a few schedule ties.
 * Fence grid (build/s42/fence_grid.py: empty asm "+r" / asm volatile "r" use of each local after each statement): best single fence.
 * ld: module loader (stat/open/read, checksum inline helper, align_up inline so the /64 stays a
 * divu, RelocateSelfSymbol + RelocateCode inline, extra RelSet relocation walk). Residual =
 * fd/size register roles (s0/s1) and the rel-count loops counting in s0. Tried: decl orders, fd
 * reused as count, register pins (fd -> s0 best).
 * The original .s stays in the build (asm/cod/000D48.s); this C
 * draft (Session 35) is kept for the record. */
typedef struct {
    unsigned int st_name;
    unsigned int st_value;
    unsigned int st_size;
    unsigned char st_info;
    unsigned char st_other;
    unsigned short st_shndx;
} Elf32_Sym;
struct Sect { int f00; void *addr; char pad08[0x14]; int offset; };
struct Rel { int type; int count; int f08; int f0C; char pad10[0x0C]; };
struct ElfInfo {
    int magic;                  /* 0x00 */
    char pad04[0x04];
    int next;                   /* 0x08 */
    char pad0C[0x18];
    int nsym;                   /* 0x24 */
    Elf32_Sym *sym;             /* 0x28 */
    char pad2C[0x04];
    struct Sect *sect;          /* 0x30 */
    int *symval;                /* 0x34 */
    int nrel;                   /* 0x38 */
    struct Rel *rel;            /* 0x3C */
};
struct LoaderStat {             /* sce_stat */
    unsigned int mode;          /* 0x00 */
    unsigned int attr;          /* 0x04 */
    unsigned int size;          /* 0x08 */
    unsigned char ctime[8];     /* 0x0C */
    unsigned char atime[8];     /* 0x14 */
    unsigned char mtime[8];     /* 0x1C */
    unsigned int hisize;        /* 0x24 */
    unsigned int private_[6];   /* 0x28 */
};
struct RelSet { struct ElfInfo *e; int nrel; struct Rel *rel; int dst; };

extern int D_00139E04;
extern int D_00131CB8[];
extern char D_00136100[];
extern char D_00136448[];   /* "ld:\tload module \"%s\"\n" */
extern char D_00136460[];   /* "Opening file \"%s\" failed(0x%x).\n" */
extern char D_00136488[];   /* "ld:\t\t0x%08x - 0x%08x (0x%08x:%x)\n" */
extern char D_00139E58[];   /* "%s.cmd" */
void LoaderSysPrintf(const char *fmt, ...);
int LoaderSysGetstat(const char *path, struct LoaderStat *st);
int LoaderSysFOpen(const char *path, int mode, int perm);
int LoaderSysFRead(int fd, void *buf, int size);
int LoaderSysFClose(int fd);
void PutString(int color, const char *fmt, ...);
int func_001285C0(const char *fmt, ...);
int func_00128A70(char *buf, const char *fmt, ...);
void RelocateElfInfoHeader(struct ElfInfo *e);
void DecodeSection(struct ElfInfo *e, void *a, void *b, void *c);
int ResolveRelocation(struct ElfInfo *m, struct Rel *r, int i);
int func_00101B88(struct ElfInfo *e, int addr, struct RelSet *set);
int OutputLinkerScriptFile(struct ElfInfo *e, char *name, void *cb);
void func_00101AA0(void);
void func_00101AC0(void);
void func_00101AF0(void);

static __inline__ int RelocateSelfSymbol(struct ElfInfo *m, unsigned int base)
{
    Elf32_Sym *s;
    struct Sect *sect;
    int *v;
    int n;
    unsigned short sh;

    n = m->nsym;
    s = m->sym;
    v = m->symval;
    sect = m->sect;
    while (n--) {
        sh = s->st_shndx;
        switch (sh) {
        case 0:
            s->st_value = base;
            break;
        case 0xfff1:
            s->st_value = *v;
            break;
        default:
            if (sh < 0xff00) {
                switch (s->st_info & 0xf) {
                case 0:
                case 1:
                case 2:
                case 3:
                    s->st_value = *v + sect[sh].f00;
                    break;
                }
            }
            break;
        }
        s++;
        v++;
    }
    return 1;
}

static __inline__ int RelocateCode(struct ElfInfo *m)
{
    struct Rel *r;
    int n, i;
    while (m != 0) {
        n = m->nrel;
        r = m->rel;
        while (n--) {
            if (r->type == 4 || r->type == 9) {
                int c = r->count;
                for (i = 0; i < c; i++)
                    ResolveRelocation(m, r, i);
            }
            r++;
        }
        if (m->next == 0)
            m = 0;
        else {
            func_001285C0(D_00136100, (char *)m + m->next);
            m = (struct ElfInfo *)((char *)m + m->next);
        }
    }
    return 1;
}

static __inline__ int checksum(unsigned char *p, int n)
{
    int sum = 0;

    while (n--)
        sum += *p++;
    return sum;
}

static __inline__ unsigned int align_up(unsigned int x, unsigned int a)
{
    return (x + a - 1) / a * a;
}

struct ElfInfo *func_00100D48(char *name)
{
    struct LoaderStat st;
    struct RelSet set;
    char buf[0x400];
    struct ElfInfo *e;
    unsigned char *p;
    long size64;
    int size, sum, i, n, tot;
    register int fd asm("$16");
    struct Rel *r;

    LoaderSysPrintf(D_00136448, name);
    fd = LoaderSysGetstat(name, &st);
    if (fd != 0 || (fd = LoaderSysFOpen(name, 1, 0)) < 0) {
        PutString(0xFFFFFF00, D_00136460, name, fd);
        return 0;
    }
    size64 = ((unsigned long)st.hisize << 32) | st.size;
    size = size64;
    D_00139E04 = align_up(D_00139E04, 0x40);
    e = (struct ElfInfo *)D_00139E04;
    D_00139E04 += size;
    LoaderSysFRead(fd, e, size);
    asm("" : "+r"(fd));
    LoaderSysFClose(fd);
    LoaderSysPrintf(D_00136488, e, (char *)e + size, size64, checksum((unsigned char *)e, size));
    set.e = e;
    set.nrel = 0;
    set.rel = (struct Rel *)0x1000000;
    set.dst = 0x1100000;
    RelocateElfInfoHeader(e);
    if (e->magic == D_00131CB8[0]) {
        n = e->nrel >> 1;
        tot = 0;
        for (i = 0; i < n; i++)
            tot += e->rel[i].count;
        func_00101B88(e, e->rel[0].f0C + tot * 8, &set);
        for (i = 0; i < n; i++)
            e->rel[n + i].count = 0;
    }
    DecodeSection(e, func_00101AC0, func_00101AF0, LoaderSysPrintf);
    RelocateSelfSymbol(e, (unsigned int)func_00101AA0);
    RelocateCode(e);
    n = set.nrel;
    r = set.rel;
    while (n--) {
        if (r->type == 4 || r->type == 9) {
            int c = r->count;
            for (i = 0; i < c; i++)
                ResolveRelocation(e, r, i);
        }
        r++;
    }
    func_00128A70(buf, D_00139E58, name);
    OutputLinkerScriptFile(e, buf, LoaderSysPrintf);
    return e;
}
