/* asm/cod/0004B8.s -> RelocateElfInfoHeader.
 * RelocateElfInfoHeader; typed info header (int offsets -> void * pointers, TBAA groups the loads), section/relocation tables walked by index (Session 23)
 * MATCHED. */
struct Sect { int f00; void *addr; char pad08[0x14]; int offset; };
struct Rel { char pad00[0x0C]; void *p0C; void *p10; int o14; int o18; };
struct ElfInfo {
    char pad00[0x14];
    int o14;
    void *p18;
    char pad1C[4];
    void *p20;
    char pad24[4];
    void *p28;
    void *p2C;
    struct Sect *sect;
    void *p34;
    int nrel;
    struct Rel *rel;
    int nsect;
    void *p44;
    void *p48;
    char pad4C[4];
    int o50;
    int o54;
    int o58;
    int o5C;
    int o60;
    int o64;
    int o68;
    int o6C;
};

void RelocateElfInfoHeader(struct ElfInfo *e) {
    int i;
    char *base = (char *)e;

    e->sect = (struct Sect *)(base + e->o5C);
    for (i = 0; i < e->nsect; i++)
        e->sect[i].addr = base + e->sect[i].offset;
    e->p28 = base + e->o54;
    e->p34 = base + e->o60;
    e->p2C = base + e->o58;
    e->p20 = base + e->o50;
    e->rel = (struct Rel *)(base + e->o64);
    e->p48 = base + e->o6C;
    e->p44 = base + e->o68;
    for (i = 0; i < e->nrel; i++) {
        e->rel[i].p0C = base + e->rel[i].o14;
        e->rel[i].p10 = base + e->rel[i].o18;
    }
    e->p18 = base + e->o14;
}
