/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 93 [cc=296].
 * DecodeSection. Same size; first is volatile (the original keeps it on the stack), type unsigned,
 * size==0 test moved after the switch. Residual = loop-invariant choice (original hoists the status-
 * name table into fp, ours the constant 2) and the s-register roles that follow from it.
 * Tried: cc=29 (552 bytes), volatile vs plain first, declaration order.
 * The original .s stays in the build (asm/cod/000278.s); this C
 * draft (Session 34) is kept for the record. */
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
    struct Sect *sh = e->sect + 1;
    volatile int first = 0;
    int n = e->nsect;
    int *names = e->names;
    const char *fmt;

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
                } else if (((int)sh->src & (sh->align - 1)) == 0) {
                    sh->addr = sh->src;
                } else {
                    sh->addr = alloc(sh->size, sh->align);
                    func_0012821C(sh->addr, sh->src, sh->size);
                    sh->status = 1;
                }
                if (log == 0)
                    break;
                if (sh->type == 1)
                    fmt = D_00136230;
                else
                    fmt = D_00136258;
                goto print;
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
                fmt = D_00136288;
            print:
                log(fmt, e->strtab + *names, sh->addr, sh->size, D_00131CC0[sh->status]);
                break;
            }
        } else {
            sh->addr = 0;
        }
        if (first == 0)
            first = (int)sh->addr;
        n--;
        sh++;
        names++;
    }
    e->entry = first + e->base;
}
