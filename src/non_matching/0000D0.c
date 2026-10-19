/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 37 [cc=296].
 * ResolveRelocation (R_MIPS_32/26/HI16/LO16). Types and the HI16 lookahead loop are right. Residual =
 * layout of the HI16 case: the original places the 'no matching LO16' printf block before the case-5
 * entry and keeps copies of the ent/val bases (inlined-helper style).
 * Tried: do-while/for/while scans, goto-placed error block, static inline get_lo helper in four shapes
 * (h3 is 404 bytes).
 * The original .s stays in the build (asm/cod/0000D0.s); this C
 * draft (Session 34) is kept for the record. */
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
        j = i;
        do {
            j++;
            t = r->ent[j].info & 0xFF;
        } while (t == 5);
        if (t == 6) {
            lo = r->val[j].offset;
        } else {
            LoaderSysPrintf(D_00136120, i);
            lo = 0;
        }
        *where = (a & 0xFFFF0000) | ((((int)(s + (a << 16) + (short)lo) >> 15) + 1) >> 1 & 0xFFFF);
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
