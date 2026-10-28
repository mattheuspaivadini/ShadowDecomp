/* KERNEL.XFF @ 0x0095E8 (336 B) - isysSearchModuleFuncNameByAddr
 * Evidence: walks the module group at .data+0x380 (isysGroupForFirst/Next, isysGroupForExit on the last object); per module an inlined search of the relocated symbol table (+0x1C: count +0x24, Elf32_Sym array +0x28, string table +0x2C; count-1 entries) for a non-SHN_ABS (0xFFF1) STT_FUNC symbol whose value is the address; on a hit strcpy's the module name (+0x38) and the symbol name into the optional buffers and returns 1. UNCONFIRMED: names.
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
    char pad20[0x18];
    char *name;
};
struct GroupEnt {
    struct ModuleObj *obj;
};
extern char D_kernel_data_0380[];
struct GroupEnt *isysGroupForFirst(void *group, int arg);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int arg);
void isysGroupForExit(struct ModuleObj *obj, int arg);
char *strcpy(char *d, const char *s);

static __inline__ char *findFuncName(struct ModRel *rel, unsigned int addr) {
    char *strtab = rel->strtab;
    Elf32_Sym *sym = rel->symtab;
    int i;

    for (i = rel->nsym - 2; i != -1; i--, sym++) {
        if (sym->st_shndx != 0xFFF1 && (sym->st_info & 0xF) == 2 && sym->st_value == addr) {
            return strtab + sym->st_name;
        }
    }
    return 0;
}

int isysSearchModuleFuncNameByAddr(char *module, char *func, unsigned int addr) {
    struct GroupEnt *g;
    struct ModuleObj *m = 0;
    int ret = 0;
    char *name;

    for (g = isysGroupForFirst(D_kernel_data_0380, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = g->obj;
        name = findFuncName(m->rel, addr);
        if (name != 0) {
            if (module != 0) {
                strcpy(module, m->name);
            }
            if (func != 0) {
                strcpy(func, name);
            }
            ret = 1;
            break;
        }
    }
    if (m != 0) {
        isysGroupForExit(m, 0);
    }
    return ret;
}
