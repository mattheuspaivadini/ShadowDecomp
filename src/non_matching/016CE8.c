/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * R4 w25a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/016CE8.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00133AA0[];
extern int D_00133AA4[];
extern int D_00133A68[];
extern int D_00133A74[];
extern int D_00133A54[];
extern int D_00133A60[];
extern int D_00150E00[];

void func_00107010(int a0);

void func_00116CE8(int *a0) {
    D_00133AA0[0] = *a0;
    D_00133AA4[0] = D_00133AA0[0];
    if (D_00133AA0[0] == 0xB) {
        D_00133AA0[0] = 0;
        D_00133A74[0] = 0;
        return;
    }
    func_00107010(D_00133A68[0]);
    if (D_00133A54[0] != 0 && D_00150E00[0] != 0)
        func_00107010(D_00133A60[0]);
    else
        D_00133A74[0] = 0;
    D_00133AA0[0] = 0;
}
