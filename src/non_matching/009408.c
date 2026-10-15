/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 15 [cc=29].
 * R2 w45a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/009408.s); this C
 * draft (Session 8) is kept for the record. */
extern int func_00109288(int a0);
extern int func_001092B8(int a0, int a1);
extern int func_00112E40(int cmd, void *p, int size, int a, int b, int c);
extern int func_001118E0(int a0, void (*a1)(), void *a2);
extern int func_001093C8(int a0, int a1, int a2, char *p);

int func_00109408(int a0, int a1) {
    int *p = (int *)a0;
    int *q;
    int f;
    int r;

    f = p[4];
    if (f & 4)
        q = (int *)func_001092B8(a1, f >> 16);
    else
        q = (int *)func_00109288(a1);
    q[5] = p[5];
    q[7] = p[7];
    q[8] = 0x8000000C;
    q[9] = p[8];
    q[10] = p[9];
    q[11] = p[10];
    r = func_00112E40(0x80000008, q, 0x40, p[8], p[9], p[10]);
    if (r != 0)
        return r;
    return func_001118E0(0x800, func_001093C8, q);
}
