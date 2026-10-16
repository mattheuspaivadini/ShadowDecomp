/* STATUS (Session 11a, 2026-10-15): NON_MATCHING. best score 1 [cc=296].
 * Session 11a R1-R3: 8 variants (028778 idiom, e-pointer, register pins);
 * residual: dbr fills the join `sll` into the first `bnez` delay ANNULLED
 * (bnezl) where the original fills it PLAIN (bnez); the plain path needs
 * `!insn_sets_resource_p (sll, &opposite_needed, 1)` at the jal - no C lever
 * found (probes + dbr source archaeology, notes_11a.md).
 * The original .s stays in the build (asm/cod/028850.s); this C
 * draft (Session 9) is kept for the record. */
extern int func_00128688(int a0);

struct S028850 {
    char pad00[0x1D4];
    int *table;                 /* 0x1D4: 32-entry handler table (028688) */
};

int func_00128850(struct S028850 *p, unsigned int i) {
    int *tbl;
    int h;

    if (i >= 0x20)
        return -1;
    tbl = p->table;
    if (tbl == 0) {
        if (func_00128688((int)p) != 0)
            return -1;
        tbl = p->table;
    }
    h = tbl[i];
    if (h == 0)
        return 1;
    if (h == -1)
        return 2;
    if (h == 1)
        return 3;
    tbl[i] = 0;
    ((void (*)(unsigned int))h)(i);
    return 0;
}
