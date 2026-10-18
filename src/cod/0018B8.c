/* asm/cod/0018B8.s -> RelocateSelfSymbol.
 * RelocateSelfSymbol; Elf32_Sym walk with while (n--), switch on a cached st_shndx and on ELF_ST_TYPE 0..3 (Session 23)
 * MATCHED. */
typedef struct { unsigned int st_name; unsigned int st_value; unsigned int st_size; unsigned char st_info; unsigned char st_other; unsigned short st_shndx; } Elf32_Sym;
typedef struct { unsigned int addr; unsigned int pad[7]; } Sect;
typedef struct { char pad00[0x24]; int nsym; Elf32_Sym *sym; int pad2C; Sect *sect; unsigned int *val; } Mod;

int RelocateSelfSymbol(Mod *m, unsigned int base) {
    Elf32_Sym *s;
    Sect *sect;
    unsigned int *v;
    int n;
    unsigned int sh;
    s = m->sym;
    v = m->val;
    n = m->nsym;
    sect = m->sect;
    while (n--) {
        sh = s->st_shndx;
        switch (sh) {
        case 0:
            s->st_value = base;
            break;
        case 0xFFF1:
            s->st_value = *v;
            break;
        default:
            if (sh < 0xFF00) {
                switch (s->st_info & 0xF) {
                case 0: case 1: case 2: case 3:
                    s->st_value = *v + sect[sh].addr;
                    break;
                }
            }
        }
        s++;
        v++;
    }
    return 1;
}
