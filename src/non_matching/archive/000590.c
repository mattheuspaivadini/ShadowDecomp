/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 000590,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/000590.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/000590.c.
 */
/* STATUS (Session 44, 2026-10-21): NON_MATCHING. best score 16 (was 28; sw.py diff lines).
 * is_section: the pre-test reads the table through a fresh zero (empty asm "+r" with an input from the outer index so loop.c cannot hoist it), the loop body loads the entry before i += 4 and the loop test reads it as int (a different TBAA type keeps gcse PRE from carrying it into the next iteration). Residual: the 2.96 ce pass (if-conversion, no -fno-if-conversion in this cc1) speculates the found flag = 1 above the strcmp test, so it cannot share v0 (image: li v0,1 in the beqz slot); return-style/branch-shape variants and two fence grids (210) did not avoid it.
 * is_section walks the table by byte offset ((int)D_00131CD0 + i, j = i; i += 4 before the strcmp) like the image's lui+addu+lw %lo. Residual: the image's first test uses a separate zero register and the loop reloads the entry at the top (ours carries the test value). Tried while/do/goto forms, -fno-strength-reduce/-fno-rerun-loop-opt/-fno-gcse.
 * linker-script writer with bwrite/bflush/is_section inline helpers. Residual = the section-name
 * table loop: the original keeps a byte offset (lui+addu+lw %lo) instead of a strength-reduced
 * pointer, and the first index is a register zero (24 bytes short). Tried: sized table, while
 * forms, -fno-strength-reduce, cc=29/2.95.
 * The original .s stays in the build (asm/cod/000590.s); this C
 * draft (Session 35) is kept for the record. */
struct Sym { int name; int value; int f08; int f0C; };
struct Sect { int addr; char pad04[0x1C]; };
struct ElfInfo {
    char pad00[0x1C];
    int nsym;                   /* 0x1C */
    int *symidx;                /* 0x20 */
    char pad24[4];
    struct Sym *sym;            /* 0x28 */
    char *strtab;               /* 0x2C */
    struct Sect *sect;          /* 0x30 */
    char pad34[0x0C];
    int nsect;                  /* 0x40 */
    int *shname;                /* 0x44 */
    char *shstrtab;             /* 0x48 */
};

extern int D_0013A180;
extern int D_00139E40;
extern char D_0013A348[];
extern char *D_00131CD0[];
extern char D_001362C0[];
extern char D_001362E8[];   /* "%s = 0x%08x;\n" */
extern char D_001362F8[];   /* "SECTIONS {\n" */
extern char D_00136308[];   /* "\t%s\t%p: {*(%s)}\n" */
extern char D_00139E48[];
int LoaderSysFOpen(const char *name, int mode, int perm);
int LoaderSysFClose(int fd);
int LoaderSysFWrite(int fd, const void *buf, int len);
int func_00128A70(char *buf, const char *fmt, ...);        /* sprintf */
unsigned int func_001290C4(const char *s);                 /* strlen */
void *func_001293B8(void *dst, const void *src, int n);    /* memcpy */
int func_00128E6C(const char *a, const char *b);           /* strcmp */

static __inline__ void bwrite(int fd, char *s)
{
    if (D_0013A180 == fd) {
        if (D_00139E40 + func_001290C4(s) >= 0x1000 && D_00139E40 != 0) {
            LoaderSysFWrite(D_0013A180, D_0013A348, D_00139E40);
            D_00139E40 = 0;
        }
        if (func_001290C4(s) >= 0x1000)
            LoaderSysFWrite(D_0013A180, s, func_001290C4(s));
        else {
            func_001293B8(D_0013A348 + D_00139E40, s, func_001290C4(s));
            D_00139E40 += func_001290C4(s);
        }
    }
}

static __inline__ void bflush(int fd)
{
    if (D_0013A180 == fd && D_00139E40 != 0) {
        LoaderSysFWrite(fd, D_0013A348, D_00139E40);
        D_00139E40 = 0;
    }
}

static __inline__ int is_section(char *name, int dep)
{
    int i;
    int j;
    char *p;

    j = 0;
    asm("" : "+r"(j) : "r"(dep));
    if (*(char **)((int)D_00131CD0 + j) != 0) {
        i = 0;
        do {
            p = *(char **)((int)D_00131CD0 + i);
            i += 4;
            if (func_00128E6C(p, name) == 0)
                return 1;
        } while (*(int *)((int)D_00131CD0 + i) != 0);
    }
    return 0;
}

int OutputLinkerScriptFile(struct ElfInfo *e, char *name, void (*cb)(char *))
{
    char buf[0x400];
    int fd;
    int i, j;
    struct Sym *s;

    if (cb != 0)
        cb(D_001362C0);
    fd = LoaderSysFOpen(name, 0x602, 0);
    D_0013A180 = fd;
    for (i = 0; i < e->nsym; i++) {
        func_00128A70(buf, D_001362E8, e->strtab + e->sym[e->symidx[i]].name, e->sym[e->symidx[i]].value);
        bwrite(fd, buf);
    }
    bwrite(fd, D_001362F8);
    for (j = 1; j < e->nsect; j++) {
        if (is_section(e->shstrtab + e->shname[j], j)) {
            func_00128A70(buf, D_00136308, e->shstrtab + e->shname[j], e->sect[j].addr,
                          e->shstrtab + e->shname[j]);
            bwrite(fd, buf);
        }
    }
    bwrite(fd, D_00139E48);
    bflush(fd);
    LoaderSysFClose(fd);
    return 1;
}
