/* KERNEL.XFF @ 0x007F48 (392 B) - func_007F48 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing]
 * Evidence: called from func_008CA8 (0x8CA8) as func_007F48(obj + 0x30, rootPtn, desc);
 * +0x00/+0x04 of the object are zeroed, then +0x04 receives iosMallocAlign(ptn,
 * *(int *)(obj + 0x00) << 3, 4) and +0x00 counts along the way (the first pass
 * does `lw 0x0(s0); addiu 1; sw`).  The descriptor (arg 2) has the group count at
 * +0x38, the group array at +0x3C, the symbol table at +0x28; the group stride is
 * 0x1C (addiu a3, a3, 0x1C) with type at +0x0 (only 4 and 9 are taken: beql 4 /
 * bnel 9), the item count at +0x4 and the 8-byte entry array at +0xC.  An entry's
 * word at +4 is shifted `srl 8; sll 4` (= index * 16) into the symtab and
 * `lhu 0xE` (= shndx) == 0 selects it, i.e. Elf32_Rel.r_info >> 8 ->
 * Elf32_Sym.st_shndx == SHN_UNDEF; the two passes (count, then fill) over
 * {group, index} pairs are byte-identical in shape.
 * Levers tried: `for (i = n - 1; i != -1; i--, g++)` and `while (i != -1)`
 * (16-89 diffs: GCC folds the trip count into `beqz ngroups`) vs the matching
 * `i = n; while (--i != -1)`; caching d->symtab in a local (s2) instead of
 * reloading it (89 -> 83); group struct size 0x1C (was 0x10, wrong stride);
 * caching/ordering of the second-pass preamble had no effect; block-scoping each
 * pass with its own locals is what reproduces the original's register reuse
 * (pass 1 g in $a3 vs pass 2 e in $a3, g in $a2) - the single-scope version
 * stays at 16/98 with a stable $a0..$a3 permutation.
 * UNCONFIRMED: names (func_007F48, struct/field names, Lst/Ent/Rel/Sym/Group),
 * pointer types of ptn, the meaning of group types 4/9 (UNCONFIRMED relocation
 * kinds), and that d is the same DldDesc modelled in 008CA8.c.
 */
struct Rel { unsigned int offset; unsigned int info; };
struct Sym {
    unsigned int name;
    unsigned int value;
    unsigned int size;
    unsigned char info;
    unsigned char other;
    unsigned short shndx;
};
struct Group { int type; int count; int pad08; struct Rel *rels; int pad14[3]; };
struct DldDesc {
    char pad00[0x0C];
    unsigned char n0C;
    char pad0D[3];
    int f10;
    char pad14[8];
    int f1C;
    char pad20[4];
    int f24;
    struct Sym *symtab;
    char pad2C[0x0C];
    int ngroups;
    struct Group *groups;
};
struct Ent { struct Group *grp; int idx; };
struct Lst { int count; struct Ent *arr; };
void *iosMallocAlign(void *ptn, int size, int align);
void func_007F48(struct Lst *lst, void *ptn, struct DldDesc *d) {
    struct Sym *sym;

    lst->count = 0;
    lst->arr = 0;
    if (d->f1C == 0)
        return;
    sym = d->symtab;
    {
        struct Group *g;
        struct Rel *r;
        int i, j;
        g = d->groups;
        i = d->ngroups;
        while (--i != -1) {
            if (g->type == 4 || g->type == 9) {
                r = g->rels;
                j = g->count;
                while (--j != -1) {
                    if (sym[r->info >> 8].shndx == 0)
                        lst->count++;
                    r++;
                }
            }
            g++;
        }
    }
    lst->arr = iosMallocAlign(ptn, lst->count << 3, 4);
    {
        struct Group *g;
        struct Rel *r;
        struct Ent *e;
        int i, j, k;
        g = d->groups;
        i = d->ngroups;
        e = lst->arr;
        while (--i != -1) {
            if (g->type == 4 || g->type == 9) {
                k = 0;
                r = g->rels;
                j = g->count;
                while (--j != -1) {
                    if (sym[r->info >> 8].shndx == 0) {
                        e->idx = k;
                        e->grp = g;
                        e++;
                    }
                    r++;
                    k++;
                }
            }
            g++;
        }
    }
}
