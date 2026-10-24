/* C equivalent of OutputLinkerScriptFile (000590, 1220 B @ 0x00100590).
 *
 * Reconstructed instruction-by-instruction from asm/cod/000590.s and the
 * REA/Ghidra Emotion Engine dossier ev_02bcb3cbb016f32dac76c44164b37c9d4f4bd3f641673acf1e3b52f9f3300964.
 * Readable reconstruction: NOT byte-exact (9 diff instructions, all inside the
 * section-name scan), not part of the build.  The codegen-tuned near-miss is
 * src/non_matching/archive/000590.c.
 *
 * Writes a GNU ld script for the loaded modules:
 *   - a callback receives the banner format with the file name (150C8: the call
 *     is jalr a2 with a0 = the format and a1 still holding `name`, so the
 *     original prototype takes (fmt, name));
 *   - every symbol of the ELF table becomes "%s = 0x%08x;\n";
 *   - "SECTIONS {\n", then one "\t%s\t%p: {*(%s)}\n" per section whose name is
 *     in the kept-section table D_00131CD0 (NULL-terminated);
 *   - "}\n", flush, close.
 *
 * Behaviour derived from the target:
 *   1005C0  beqz a2 / jalr a2        -> if (cb) cb(fmt, name)
 *   1005D8  addiu a1,0x602           -> LoaderSysFOpen(name, 0x602, 0)
 *   1007F0  lui/addiu/addu/lw        -> D_00131CD0[i] walked as byte offsets
 *   100810  lbu-style 4-byte step    -> the table is char *[] (stride 4)
 *   100828  beqz v0 / li v0,1        -> return 1 on the first match
 *   101... the write helper buffers up to 0x1000 bytes in D_0013A348
 */
struct Sym {
    int name;                       /* 0x00: strtab offset */
    int value;                      /* 0x04 */
    int f08;                        /* 0x08 */
    int f0C;                        /* 0x0C */
};

struct Sect {
    int addr;                       /* 0x00 */
    char pad04[0x1C];
};

struct ElfInfo {
    char pad00[0x1C];
    int nsym;                       /* 0x1C */
    int *symidx;                    /* 0x20 */
    char pad24[4];
    struct Sym *sym;                /* 0x28 */
    char *strtab;                   /* 0x2C */
    struct Sect *sect;              /* 0x30 */
    char pad34[0x0C];
    int nsect;                      /* 0x40 */
    int *shname;                    /* 0x44 */
    char *shstrtab;                 /* 0x48 */
};

extern int D_0013A180;              /* the file being written */
extern int D_00139E40;              /* bytes buffered in D_0013A348 */
extern char D_0013A348[];           /* 0x1000-byte write buffer */
extern char *D_00131CD0[];          /* kept-section names, NULL-terminated */
extern char D_001362C0[];           /* "ld:\toutput linker script \x1b[32m\"%s\"\x1b[m.\n" */
extern char D_001362E8[];           /* "%s = 0x%08x;\n" */
extern char D_001362F8[];           /* "SECTIONS {\n" */
extern char D_00136308[];           /* "\t%s\t%p: {*(%s)}\n" */
extern char D_00139E48[];           /* "}\n" */

int LoaderSysFOpen(const char *name, int mode, int perm);
int LoaderSysFClose(int fd);
int LoaderSysFWrite(int fd, const void *buf, int len);
int func_00128A70(char *buf, const char *fmt, ...);     /* sprintf */
unsigned int func_001290C4(const char *s);              /* strlen */
void *func_001293B8(void *dst, const void *src, unsigned int n);  /* memcpy */
int func_00128E6C(const char *a, const char *b);        /* strcmp */

static __inline__ void bwrite(int fd, char *s)
{
    unsigned int len = func_001290C4(s);

    if (D_0013A180 != fd)
        return;
    if (D_00139E40 != 0 && D_00139E40 + len >= 0x1000) {
        LoaderSysFWrite(D_0013A180, D_0013A348, D_00139E40);
        D_00139E40 = 0;
    }
    if (len >= 0x1000) {
        LoaderSysFWrite(D_0013A180, s, len);
    } else {
        func_001293B8(D_0013A348 + D_00139E40, s, len);
        D_00139E40 += len;
    }
}

static __inline__ void bflush(int fd)
{
    if (D_0013A180 != fd || D_00139E40 == 0)
        return;
    LoaderSysFWrite(fd, D_0013A348, D_00139E40);
    D_00139E40 = 0;
}

/* Is `name` in the kept-section table?  (The `dep` index is the caller's
 * section index; the scan itself is over the whole NULL-terminated table.) */
static __inline__ int is_section(char *name)
{
    int i;

    if (D_00131CD0[0] == 0)
        return 0;
    for (i = 0; D_00131CD0[i] != 0; i++)
        if (func_00128E6C(D_00131CD0[i], name) == 0)
            return 1;
    return 0;
}

int OutputLinkerScriptFile(struct ElfInfo *e, char *name,
                           void (*cb)(const char *fmt, const char *name))
{
    char buf[0x400];
    int fd;
    int i, j;
    struct Sym *s;
    char *sectname;

    if (cb != 0)
        cb(D_001362C0, name);
    fd = LoaderSysFOpen(name, 0x602, 0);
    D_0013A180 = fd;

    for (i = 0; i < e->nsym; i++) {
        s = &e->sym[e->symidx[i]];
        func_00128A70(buf, D_001362E8, e->strtab + s->name, s->value);
        bwrite(fd, buf);
    }

    bwrite(fd, D_001362F8);
    for (j = 1; j < e->nsect; j++) {
        sectname = e->shstrtab + e->shname[j];
        if (is_section(sectname)) {
            func_00128A70(buf, D_00136308, sectname, e->sect[j].addr,
                          sectname);
            bwrite(fd, buf);
        }
    }
    bwrite(fd, D_00139E48);
    bflush(fd);
    LoaderSysFClose(fd);
    return 1;
}
