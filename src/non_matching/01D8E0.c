/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 10 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01D8E0.s); this C
 * draft (Session 9) is kept for the record. */
int func_00121E88(int a0);
int func_00120490(int a0);
int func_001204B0(int a0);
int func_00121698(int a0);
extern char D_0015DF48[];

int func_0011D8E0(int a0) {
    int id = a0;
    char *p;
    int r;

    if (func_00121E88(a0) == 0)
        return 0x81010013;
    if (func_00120490(id) == 0)
        return 0x81019003;
    p = D_0015DF48 + 0x898 * id;
    r = *(int *)(p + 0x888);
    if (r == 1)
        return 0x81019003;
    if (*(int *)(p + 0x88C) != 0)
        return 0x8101002F;
    if (func_001204B0(id) == 0)
        return 0x81010013;
    func_00121698(id);
    return 0;
}
