/* asm/cod/001518.s -> LoaderSysRelocateOnlineElfInfo.
 * LoaderSysRelocateOnlineElfInfo; MoveElf's symbol fix-up switch + RelocateCode static inline, caller-supplied callbacks (Session 35)
 * MATCHED. */
typedef struct {
    unsigned int st_name;
    unsigned int st_value;
    unsigned int st_size;
    unsigned char st_info;
    unsigned char st_other;
    unsigned short st_shndx;
} Elf32_Sym;
struct Sect { int f00; void *addr; char pad08[0x14]; int offset; };
struct Rel { int type; int count; char pad08[0x14]; };
struct ElfInfo {
    char pad00[0x08];
    int next;                   /* 0x08 */
    char pad0C[0x04];
    int entry;                  /* 0x10 */
    int size;                   /* 0x14 */
    char pad18[0x0C];
    int nsym;                   /* 0x24 */
    Elf32_Sym *sym;             /* 0x28 */
    char pad2C[0x04];
    struct Sect *sect;          /* 0x30 */
    int *symval;                /* 0x34 */
    int nrel;                   /* 0x38 */
    struct Rel *rel;            /* 0x3C */
};

extern char D_00136100[];
extern char D_001364B0[];   /* "%p: %x => %p\n" */
extern char D_001364C0[];   /* "entry: %p\n" */
int LoaderSysPrintf(const char *fmt, ...);
int func_001285C0(const char *fmt, ...);
void *func_001282CC(void *dst, const void *src, int n);   /* memcpy */
int FlushCache(int mode);
void RelocateElfInfoHeader(struct ElfInfo *e);
int DecodeSection(struct ElfInfo *e, void *a, void *b, void *c);
int ResolveRelocation(struct ElfInfo *m, struct Rel *r, int i);
void func_00101AA0(void);
void func_00101AC0(void);
void func_00101AF0(void);

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

int LoaderSysRelocateOnlineElfInfo(struct ElfInfo *e, void *alloc, void *alloc2, unsigned int undef, void *pr)
{
    Elf32_Sym *sym;
    int *val;
    struct Sect *sect;
    int n;
    unsigned short idx;

    RelocateElfInfoHeader(e);
    DecodeSection(e, alloc, alloc2, pr);
    n = e->nsym;
    sym = e->sym;
    val = e->symval;
    sect = e->sect;
    while (n--) {
        idx = sym->st_shndx;
        switch (idx) {
        case 0:
            sym->st_value = undef;
            break;
        case 0xfff1:
            sym->st_value = *val;
            break;
        default:
            if (idx < 0xff00) {
                switch (sym->st_info & 0xf) {
                case 0:
                case 1:
                case 2:
                case 3:
                    sym->st_value = *val + sect[idx].f00;
                    break;
                }
            }
            break;
        }
        sym++;
        val++;
    }
    return RelocateCode(e);
}
