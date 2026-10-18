/* asm/cod/001800.s -> FreeDecodedSection.
 * FreeDecodedSection; typed module/section records, continue on unloaded sections, printf declared int-returning (Session 23)
 * MATCHED. */
struct Sect { void *addr; char pad04[0x14]; int loaded; char pad1C[4]; };
struct Mod { char pad00[0x08]; int next; char pad0C[0x24]; struct Sect *sect; char pad34[0x0C]; int nsect; };
extern char D_00136100[];
int func_001285C0(const char *fmt, ...);   /* printf (see config/symbol_addrs.txt) */

int FreeDecodedSection(struct Mod *m, void (*cb)(void *)) {
    int i;
    struct Sect *s;
    while (m != 0) {
        for (i = 1; i < m->nsect; i++) {
            s = &m->sect[i];
            if (s->loaded == 0) continue;
            s->loaded = 0;
            cb(s->addr);
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
