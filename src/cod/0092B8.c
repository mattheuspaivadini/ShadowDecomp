/* asm/cod/0092B8.s -> func_001092B8.
 * SCE sifrpc record lookup; out-of-range falls back to the ring cursor (Session 19)
 * MATCHED. */
struct S0092B8 {
    char pad[0x1C];
    char *table;    /* 0x1C: 64-byte records */
    int count;      /* 0x20 */
};

char *func_00109288(struct S0092B8 *p);

char *func_001092B8(struct S0092B8 *p, int idx) {
    if (idx < 0 || idx >= p->count)
        return func_00109288(p);
    return p->table + idx * 64;
}
