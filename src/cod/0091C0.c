/* asm/cod/0091C0.s -> func_001091C0.
 * Counter-wrap result held in a separate variable assigned on both arms of an if/else (r = 1 / r = id): the explicit r = 1 survives cse as its own set, giving the rematerialised addiu 1 in the wrap path (Session 26).
 * MATCHED. */
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
    int r;

    DIntr();
    p = pool->items;
    for (i = 0; i < pool->n; i++, p++) {
        if ((p->mode & 1) == 0) {
            p->mode = (i << 16) | 5;
            id = ++pool->counter;
            if (id == 1) {
                pool->counter++;
                r = 1;
            } else
                r = id;
            p->self = p;
            p->id = r;
            EIntr();
            return p;
        }
    }
    EIntr();
    return 0;
}
