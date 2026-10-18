/* STATUS (Session 28, 2026-10-18): NON_MATCHING. best score 14 [cc=29].
 * Poll failure as goto fail to a shared return 0 reproduces the original block layout (Wait fall-through, Poll after it; any if/else/switch spelling gives Poll as fall-through). Residual = global-alloc roles: original a2->s0, a1->s1, base->s2, ours a1->s0, base->s1, a2->s2 (permute_gen/types/stmts ~1500 variants: no gain). Session 23: struct-pointer base fixes the s2 base and both *a1 stores.
 * The original .s stays in the build (asm/cod/01B670.s); this C
 * draft (Session 28) is kept for the record. */
struct R { int f00; int stat; int f08; };
extern struct R D_00151900;
extern int D_00151E28[];
int WaitSema(int s);
int PollSema(int s);

int func_0011B670(int mode, int *a1, int *a2) {
    struct R *r = &D_00151900;
    if (r->stat == 0) return -1;
    if (a1) *a1 = r->stat;
    if (mode == 0) WaitSema(D_00151E28[0]);
    else if (PollSema(D_00151E28[0]) < 0) goto fail;
    if (a2) *a2 = r->f08;
    if (a1) *a1 = r->stat;
    r->stat = 0;
    return 1;
fail:
    return 0;
}
