/* KERNEL.XFF @ 0x0097A0 (368 B) - isysSearchModuleSymbolByGroup
 * Evidence: walks the given module group skipping one module; per module MakeStrHashValue(name), then modules flagged 0x80000000 (+0x2C) look the key up with SearchStrHashKey(.bss+0xDE58) (value = entry->+8->+4), others scan count-1 symbols with strcmp; the hit stores the value through the first argument and the module is returned (kept on the stack: all s-registers busy). The original symbol loop never advances its pointer (only the first Elf32_Sym is ever compared), reproduced as is. UNCONFIRMED: names.
 */
typedef struct {
    unsigned int st_name;
    unsigned int st_value;
    unsigned int st_size;
    unsigned char st_info;
    unsigned char st_other;
    unsigned short st_shndx;
} Elf32_Sym;
struct ModRel {
    char pad0[0x24];
    int nsym;
    Elf32_Sym *symtab;
    char *strtab;
};
struct ModuleObj {
    char pad0[0x1C];
    struct ModRel *rel;
    char pad20[0xC];
    unsigned int flags;
};
struct GroupEnt {
    struct ModuleObj *obj;
};
struct HashEnt {
    int unk0;
    int unk4;
    int *value;
};
extern char D_kernel_bss_DE58[];
struct GroupEnt *isysGroupForFirst(void *group, int arg);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int arg);
void isysGroupForExit(struct ModuleObj *obj, int arg);
char *MakeStrHashValue(const char *s);
struct HashEnt *SearchStrHashKey(void *table, const char *key);
int strcmp(const char *a, const char *b);

static __inline__ int findSymbol(int *out, char *name, struct ModuleObj *m) {
    char *key = MakeStrHashValue(name);
    struct ModRel *rel = m->rel;
    struct HashEnt *e;
    char *strtab;
    Elf32_Sym *sym;
    int i;

    if (m->flags & 0x80000000) {
        e = SearchStrHashKey(D_kernel_bss_DE58, key);
        if (e != 0) {
            *out = e->value[1];
            return 1;
        }
        return 0;
    }
    strtab = rel->strtab;
    sym = rel->symtab;
    for (i = rel->nsym - 2; i != -1; i--) {
        if (sym->st_shndx != 0 && strcmp(strtab + sym->st_name, name) == 0) {
            *out = sym->st_value;
            return 1;
        }
    }
    return 0;
}

struct ModuleObj *isysSearchModuleSymbolByGroup(int *out, char *name, void *group, struct ModuleObj *skip) {
    struct GroupEnt *g;
    struct ModuleObj *m = 0;
    struct ModuleObj *found = 0;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = g->obj;
        if (m == skip) {
            continue;
        }
        if (findSymbol(out, name, m)) {
            found = m;
            break;
        }
    }
    if (m != 0) {
        isysGroupForExit(m, 0);
    }
    return found;
}
