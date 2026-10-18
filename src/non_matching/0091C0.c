/* STATUS (Session 22, 2026-10-17): NON_MATCHING. best score 5 [cc=29].
 * typed pool/item structs; residual = the id = 1 rematerialisation in the counter-wrap branch
 * The original .s stays in the build (asm/cod/0091C0.s); this C
 * draft (Session 22) is kept for the record. */
struct Item09 {
    char pad00[0x10];
    int mode;                   /* 0x10 */
    struct Item09 *self;        /* 0x14 */
    int id;                     /* 0x18 */
    char pad1C[0x24];
};
struct Pool09 {
    int counter;                /* 0x0 */
    struct Item09 *items;       /* 0x4 */
    int n;                      /* 0x8 */
};

void DIntr(void);
void EIntr(void);

struct Item09 *func_001091C0(struct Pool09 *pool) {
    struct Item09 *p;
    int i;
    int id;

    DIntr();
    p = pool->items;
    for (i = 0; i < pool->n; i++, p++) {
        if ((p->mode & 1) == 0) {
            p->mode = (i << 16) | 5;
            id = ++pool->counter;
            if (id == 1)
                pool->counter++;
            p->self = p;
            p->id = id;
            EIntr();
            return p;
        }
    }
    EIntr();
    return 0;
}
