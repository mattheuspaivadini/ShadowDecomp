/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * size 60 vs 64: branch-likely bounds check not reproduced.
 * See docs/progress.md for the family classification. */
/* func_001092B8 @ 0x001092B8 (0x40 bytes): bounds-checked table lookup,
 * 64-byte records; out of range forwards to func_00109288. */
int *func_00109288(struct S0092B8 *p, int idx);

struct S0092B8 {
    char pad[0x1C];
    int *table;    /* 0x1C */
    int  count;    /* 0x20 */
};

int *func_001092B8(struct S0092B8 *p, int idx) {
    if (idx >= 0 && idx < p->count)
        return (int *)((char *)p->table + idx * 64);
    return func_00109288(p, idx);
}
