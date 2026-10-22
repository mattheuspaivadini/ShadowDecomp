/* asm/cod/0000D0.s -> ResolveRelocation.
 * loader ResolveRelocation (R_MIPS_32/26/HI16/LO16): HI16 lookahead as a for(;;) with continue/break (error block ahead of the case), entry address as int sum (j << 3), s + (a << 16) in its own temp (Session 41)
 * MATCHED. */
struct Sect { void *addr; char pad04[0x1C]; };
struct Sym { int name; unsigned int value; int size; int info; };
struct RelEnt { unsigned int offset; unsigned int info; };
struct Rel { int type; int count; int sect; struct RelEnt *ent; struct RelEnt *val; };
struct ElfInfo {
    char pad00[0x28];
    struct Sym *sym;
    void *p2C;
    struct Sect *sect;
};

extern char D_00136120[];
extern char D_00136160[];
int LoaderSysPrintf(const char *fmt, ...);

int ResolveRelocation(struct ElfInfo *e, struct Rel *r, int i) {
    struct RelEnt *ent = &r->ent[i];
    unsigned int type = ent->info & 0xFF;
    unsigned int *where = (unsigned int *)((char *)e->sect[r->sect].addr + ent->offset);
    unsigned int s = e->sym[ent->info >> 8].value;
    unsigned int a = r->val[i].offset;
    int lo;
    unsigned int t;
    unsigned int hs;
    int j;

    switch (type) {
    case 0:
        break;
    case 2:
        *where = a + s;
        break;
    case 4:
        *where = a + ((s >> 2) & 0x3FFFFFF);
        break;
    case 5:
        j = i + 1;
        for (;;) {
            t = ((struct RelEnt *)((int)r->ent + (j << 3)))->info & 0xFF;
            if (t == 5) {
                j++;
                continue;
            }
            if (t != 6) {
                LoaderSysPrintf(D_00136120, i);
                lo = 0;
                break;
            }
            lo = r->val[j].offset;
            break;
        }
        hs = s + (a << 16);
        *where = (a & 0xFFFF0000) | ((((int)(hs + (short)lo) >> 15) + 1) >> 1 & 0xFFFF);
        break;
    case 6:
        *where = (a & 0xFFFF0000) | ((s + a) & 0xFFFF);
        break;
    default:
        LoaderSysPrintf(D_00136160, type, ent->offset);
        return 0;
    }
    return 1;
}
