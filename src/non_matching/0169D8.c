/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 14 [cc=29].
 * R3 famB: 0x2081 guard + func_00109B80 gate
 * The original .s stays in the build (asm/cod/0169D8.s); this C
 * draft (Session 8) is kept for the record. */
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00107020(int a0);
int func_00107000(int a0);
int func_00109B80(int a0);
void func_00116C58(int a0, ...);

extern int D_00150DC0[];    /* lui/%lo: the DBC lock word */
extern int D_0014E950[];    /* .bss 0x0014E950, 0x28 bytes, lui/%lo */
extern int D_0014EAC0[];    /* .bss 0x0014EAC0, lui/%lo */
extern char D_001387F8[];   /* lui/%lo: the "too big" message */
extern char D_00138828[];   /* lui/%lo: the busy message */

int func_001169D8(int a0, int a1, int *a2, char *a3, int a4) {
    int i;

    if (*a2 >= 0x2081) {
        func_00116C58((int)D_001387F8, *a2);
        return 0;
    }
    func_00107020(D_00150DC0[0]);
    if (func_00109B80((int)D_0014E950) == 1) {
        func_00116C58((int)D_00138828);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    D_0014EAC0[0] = a0;
    D_0014EAC0[1] = a1;
    D_0014EAC0[2] = *a2;
    for (i = 0; i < *a2; i++)
        ((char *)D_0014EAC0)[0xC + i] = a3[i];
    if (func_00109980((int)D_0014E950, 0x8000131C, 1, (int)D_0014EAC0, 0x2090,
                      (int)D_0014EAC0, 0x2090, a4, 0) < 0) {
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    func_00107000(D_00150DC0[0]);
    return 1;
}
