/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 9 [cc=29].
 * branch-likely delay slot scheduling
 * The original .s stays in the build (asm/cod/0092B8.s); this C
 * draft (Session 8) is kept for the record. */
struct S0092B8 {
    char pad[0x1C];
    int *table;
    int count;
};

int *func_00109288(struct S0092B8 *p, int idx);

int *func_001092B8(struct S0092B8 *p, int idx) {
    if (idx >= 0 && idx < p->count)
        return (int *)((char *)p->table + idx * 64);
    return func_00109288(p, idx);
}
