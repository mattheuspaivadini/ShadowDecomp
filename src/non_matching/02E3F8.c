/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 3 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02E3F8.s); this C
 * draft (Session 9) is kept for the record. */
struct N2E3F8 {
    struct N2E3F8 *next;    /* 0x00 */
    int count;              /* 0x04 */
    char *items;            /* 0x08 */
};

int func_0012E3F8(char *base, int (*cb)(void *)) {
    struct N2E3F8 *n;
    char *item;
    int r = 0;
    int i;

    for (n = (struct N2E3F8 *)(base + 0x1D8); n != 0; n = n->next) {
        item = n->items;
        for (i = n->count - 1; i >= 0; i--) {
            if (*(short *)(item + 0xC) != 0)
                r |= cb(item);
            item += 0x58;
        }
    }
    return r;
}
