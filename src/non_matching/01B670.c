/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 21 [cc=29].
 * struct-pointer base reproduces the s2 base and both *a1 stores; residual = Wait/Poll block order and $s0/$s1 roles of a1/a2
 * The original .s stays in the build (asm/cod/01B670.s); this C
 * draft (Session 23) is kept for the record. */
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
    else if (PollSema(D_00151E28[0]) < 0) return 0;
    if (a2) *a2 = r->f08;
    if (a1) *a1 = r->stat;
    r->stat = 0;
    return 1;
}
