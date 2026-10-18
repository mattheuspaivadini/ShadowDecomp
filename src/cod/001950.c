/* asm/cod/001950.s -> DisposeRelocationElement.
 * DisposeRelocationElement; typed 0x1C relocation records, third argument forwarded to the callback (Session 23)
 * MATCHED. */
struct Rel { int f00; int size; int f08; int addr; char pad10[0x0C]; };
struct Mod { int magic; char pad04[0x34]; int nrel; struct Rel *rel; };
extern int D_00131CB8[];

/* The third argument is passed through to the callback untouched (a2 is
 * live but never written in the original). */
void DisposeRelocationElement(struct Mod *m, void (*cb)(struct Mod *, int, int), int arg) {
    int n, i, sum;
    if (m->magic != D_00131CB8[0]) return;
    n = m->nrel >> 1;
    sum = 0;
    for (i = 0; i < n; i++)
        sum += m->rel[i].size;
    cb(m, m->rel[0].addr + sum * 8, arg);
    for (i = 0; i < n; i++)
        m->rel[n + i].size = 0;
}
