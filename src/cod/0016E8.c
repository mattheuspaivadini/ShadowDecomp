/* asm/cod/0016E8.s -> RelocateCode.
 * RelocateCode; typed relocation-section records, while (n--) walk, int-returning ResolveRelocation/printf (Session 23)
 * MATCHED. */
struct Rel { int type; int count; char pad08[0x14]; };
struct Mod { char pad00[0x08]; int next; char pad0C[0x2C]; int nrel; struct Rel *rel; };
extern char D_00136100[];
int ResolveRelocation(struct Mod *m, struct Rel *r, int i);
int func_001285C0(const char *fmt, ...);   /* printf (see config/symbol_addrs.txt) */

int RelocateCode(struct Mod *m) {
    struct Rel *r;
    int n, i;
    while (m != 0) {
        n = m->nrel;
        r = m->rel;
        while (n--) {
            if (r->type == 4 || r->type == 9) {
                int c = r->count;
                for (i = 0; i < c; i++)
                    ResolveRelocation(m, r, i);
            }
            r++;
        }
        if (m->next == 0)
            m = 0;
        else {
            func_001285C0(D_00136100, (char *)m + m->next);
            m = (struct Mod *)((char *)m + m->next);
        }
    }
    return 1;
}
