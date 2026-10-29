/* KERNEL.XFF @ 0x007400 (156 B) - Shock_Request  [PARKED, 164 B / ~32 words]
 * STATUS: NOT MATCHING. Prior draft (build/s70) 27/39 words. New negatives (S72 helper):
 *  - orig compares count/b UNSIGNED (sltu): make table count `unsigned int` and `b` unsigned.
 *  - orig 3rd callee arg = lui 0xFFFF; dsrl32 0; and -> `(unsigned long)id.w & 0xFFFFFFFFUL`, callee id param unsigned long (reproduced).
 *  - orig reads the spilled byte ONCE (t1 reused for count test and index): `unsigned char ix = id.b[0]` (still 164 B).
 *  - residual: mine hoists `e = 0` above the lbu and leaves a nop in the beqz slot (orig: `move a2,zero` IS the delay slot);
 *    else-branch `e = 0` form (beqzl) and ternary also tried -> worse.
 */
struct ShockEntryHdr {
    char pad[8];
    unsigned short count;
};
struct ShockEntry {
    struct ShockEntryHdr *hdr;
    char pad[8];
    int *items;
};
struct ShockTable {
    unsigned int count;
    struct ShockEntry **entries;
};
struct ShockResult {
    char pad[0x3C];
    int *item;
};
union ShockId {
    int w;
    unsigned char b[4];
};
extern struct ShockTable *D_kernel_data_0368;
struct ShockResult *func_0070B8(int a, int *it, unsigned long id);

struct ShockResult *Shock_Request(int a, unsigned int b, int c) {
    volatile union ShockId id;
    struct ShockEntry *e;
    int *it;
    unsigned char ix;

    id.w = c;
    ix = id.b[0];
    e = 0;
    if (ix < D_kernel_data_0368->count)
        e = D_kernel_data_0368->entries[ix];
    it = 0;
    if (e != 0 && b < e->hdr->count)
        it = e->items + b;
    if (it == 0)
        return 0;
    {
        struct ShockResult *r = func_0070B8(a, it, (unsigned long)id.w & 0xFFFFFFFFUL);

        if (r != 0)
            r->item = it;
        return r;
    }
}
