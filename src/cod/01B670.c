/* asm/cod/01B670.s -> func_0011B670.
 * Poll failure as goto to a shared return 0; a2 pinned to s0 with a register asm local fixes the global-alloc roles (Session 32).
 * MATCHED. */
struct R { int f00; int stat; int f08; };
extern struct R D_00151900;
extern int D_00151E28[];
int WaitSema(int s);
int PollSema(int s);

int func_0011B670(int mode, int *a1, int *a2_) {
    register int *a2 asm("$16") = a2_; /* global alloc order: a2 -> s0, a1 -> s1, base -> s2 */
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
