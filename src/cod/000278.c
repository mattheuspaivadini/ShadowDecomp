/* asm/cod/000278.s -> DecodeSection.
 * loader DecodeSection: per-type log calls written out (no shared goto), misaligned-source branch first, first-address kept in a one-element stack array (Session 41)
 * MATCHED. */
struct Sect {
    void *addr;                 /* 0x00 */
    void *src;                  /* 0x04 */
    int size;                   /* 0x08 */
    int align;                  /* 0x0C */
    unsigned int type;          /* 0x10 */
    int high;                   /* 0x14 */
    int status;                 /* 0x18 */
    int pad1C;
};
struct ElfInfo {
    char pad00[0x10];
    int entry;                  /* 0x10 */
    char pad14[0x1C];
    struct Sect *sect;          /* 0x30 */
    char pad34[0xC];
    int nsect;                  /* 0x40 */
    int *names;                 /* 0x44 */
    int strtab;                 /* 0x48 */
    int base;                   /* 0x4C */
};

extern char D_00136218[];
extern char D_00136230[];
extern char D_00136258[];
extern char D_00136288[];
extern char *D_00131CC0[];

void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */
void *func_001283D0(void *dst, int c, unsigned int size);         /* memset */

void DecodeSection(struct ElfInfo *e, void *(*alloc)(int, int), void *(*alloc_high)(int),
                   int (*log)(const char *, ...)) {
    struct Sect *sh;
    int first[1];
    int n;
    int *names;
    const char *fmt;

    sh = e->sect + 1;
    first[0] = 0;
    n = e->nsect;
    names = e->names;
    if (log != 0)
        log(D_00136218);
    n -= 2;
    while (n != -1) {
        sh->status = 0;
        if (sh->size != 0) {
            switch (sh->type) {
            case 1:
            case 0x7FFFF420:
                if (sh->high != 0) {
                    sh->addr = alloc_high(sh->size);
                    func_0012821C(sh->addr, sh->src, sh->size);
                    sh->status = 2;
                } else if (((int)sh->src & (sh->align - 1)) != 0) {
                    sh->addr = alloc(sh->size, sh->align);
                    func_0012821C(sh->addr, sh->src, sh->size);
                    sh->status = 1;
                } else {
                    sh->addr = sh->src;
                }
                if (log == 0)
                    break;
                if (sh->type == 1)
                    log(D_00136230, e->strtab + *names, sh->addr, sh->size, D_00131CC0[sh->status]);
                else
                    log(D_00136258, e->strtab + *names, sh->addr, sh->size, D_00131CC0[sh->status]);
                break;
            case 8:
                if (sh->high != 0) {
                    sh->addr = alloc_high(sh->size);
                    sh->status = 2;
                } else {
                    sh->addr = alloc(sh->size, sh->align);
                    sh->status = 1;
                }
                func_001283D0(sh->addr, 0, sh->size);
                if (log == 0)
                    break;
                log(D_00136288, e->strtab + *names, sh->addr, sh->size, D_00131CC0[sh->status]);
                break;
            }
        } else {
            sh->addr = 0;
        }
        if (first[0] == 0)
            first[0] = (int)sh->addr;
        n--;
        sh++;
        names++;
    }
    e->entry = first[0] + e->base;
}
