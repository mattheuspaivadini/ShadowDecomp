/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 2 [cc=29].
 * movn-ifconversion: `return v ? v : -0x21C` needs addiu+movn with lw in the bgezl delay; wave3d (R1)
 * The original .s stays in the build (asm/cod/018870.s); this C
 * draft (Session 8) is kept for the record. */
int func_00118438(int *p, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int func_00118870(int a0, int a1, int a2) {
    int v;

    v = func_00118438((int *)a0, a1, 1, a2, 0x40);
    if (v < 0)
        return v;
    if (func_00118380(a0, 1, (int *)a1, 0x44, 4) < 0)
        return -0x21E;
    v = *(int *)a1;
    return v ? v : -0x21C;
}
